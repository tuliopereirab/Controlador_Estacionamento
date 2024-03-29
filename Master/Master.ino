#include <Wire.h>

#define nLedsVerm 8
#define nSensores 2

int *vagas, nCarrosEst = 0;
int nVagas = 16;
int *ledVerm, *ledEntrada;
int *trig, *echo;

int trancarEntrada = 0;   // evita duas entradas simultâneas (uma em cada sensor);
int contadorEntrada = 1000;  // conta o tempo entre uma entrada e a liberação para a próxima
int contador = 0;         // conta o tempo de verificação dos sensores
int statusSaida = 0;      // evita que sejam feitas duas chamadas da função saída quando for digitado um valor qualquer (tranca e depois libera)
int flagEnvia = 0;
int codeGlobal, ledPiscante;

ISR(TIMER1_OVF_vect) {    // conta o tempo necessário para entrada e libera a entrada após esse tempo
  int i;
  contadorEntrada++;
  if (contadorEntrada == 500) {
    //enviarSerial(55);
    codeGlobal = 55;
    flagEnvia = 1;
//    Wire.beginTransmission(8);
//    Wire.write(55);
//    Wire.endTransmission();

    trancarEntrada = 0;
    atualizaLedsLigados();    // chama uma atualização para definir quais leds serão mantidos ligados ou não
    for(i=0; i<nSensores; i++)
        digitalWrite(ledEntrada[i], LOW);     // desliga os dois leds indicando a entrada trancada
    Serial.println("Entrada liberada!");
  }
}

ISR(TIMER2_OVF_vect) {   // verifica os sensores a cada período de tempo
  float distancia;
  TCNT2 = 0;
  contador++;
  if (contador == 20) {
    distancia = verDistancia(0);  // verificação NORTE
    //Serial.print("Distancia Norte: ");
    //Serial.println(distancia);
    if ((distancia < 4) && (distancia != 0) && (trancarEntrada == 0)) { // verifica presença de algum carro e se já existe uma entrada em andamento
      Serial.println("Entrada Norte!");
      trancarEntrada = 1;     // tranca a entrada enquanto se passa o tempo de entrada de 1 carro
      contadorEntrada = 0;     // inicia a contar o tempo no Timer entrada
      entrada(0);
    }//else Serial.println("Sem entrada SUL.");

    distancia = verDistancia(1);  // verificação SUL
    //Serial.print("Distancia Sul: ");
    //Serial.println(distancia);
    if ((distancia < 7) && (distancia != 0) && (trancarEntrada == 0)) {
      Serial.println("Entrada Sul!");
      trancarEntrada = 1;   // tranca a entrada enquanto se passa o tempo de entrada de 1 carro
      contadorEntrada = 0;     // inicia a contar o tempo no Timer entrada
      entrada(1);
    }//else Serial.println("Sem entrada NORTE.");
    contador = 0;
  }
}


void setup() {
  Wire.begin();
  Serial.begin(9600);
  vagas = (int*)malloc(sizeof(int) * nVagas);       // aloca o número de vagas
  ledVerm = (int*)malloc(sizeof(int) * nLedsVerm); // aloca o vetor de leds vermelhos
  ledEntrada = (int*)malloc(sizeof(int)* nSensores);
  trig = (int*)malloc(sizeof(int) * nSensores);
  echo = (int*)malloc(sizeof(int) * nSensores);
  inicializar();       // inicializa vagas vazias e leds apagados, assim como os pinos de cada led. Inicializa também os TIMERS
  int i;
  for (i = 0; i < nLedsVerm; i++) {
    pinMode(ledVerm[i], OUTPUT);   // inicializa os leds vermelhos
  }
  for (i = 0; i < nSensores; i++) {
    pinMode(ledEntrada[i], OUTPUT);
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
  codeGlobal = 55;
  flagEnvia = 1;
  //enviarSerial(55);
  Serial.println("Pronto!");
}

void inicializar() {
  int i;
  for (i = 0; i < nVagas; i++) {
    vagas[i] = 0; // indica que todas as vagas estão vazias
  }
  inicializaLeds();
  inicializaSensores();
  inicializaTimers();
  for (i = 0; i < nLedsVerm; i++) {
    digitalWrite(ledVerm[i], LOW);    // desliga todos os leds vermelhos
  }
  Serial.println("Inicializado...");
}

void inicializaLeds() {    // mapeamento dos pinos dos LEDS
  ledVerm[0] = A1;
  ledVerm[1] = A2;
  ledVerm[2] = 3;
  ledVerm[3] = 4;
  ledVerm[4] = 5;
  ledVerm[5] = 6;
  ledVerm[6] = 7;
  ledVerm[7] = 8;
  ledEntrada[0] = A0;
  ledEntrada[1] = A3;
  
  Serial.println("Pinos dos leds setados...");
}

void inicializaSensores() {
  trig[0] = 12; // norte
  trig[1] = 10; // sul

  echo[0] = 11; // norte
  echo[1] = 9; // sul
}

void inicializaTimers() {
  TCCR1A = 0; //confira timer para operação normal
  TCCR1B = 0; //limpa registrador
  TIMSK1 |= (1 << TOIE1);
  TCCR1B = 1; // modo normal sem prescaler
  TCNT1 = 0;

  TCCR2A  = 0; //timer operando em modo normal, registrador de
  TCCR2B  = 7; //prescaler 1:1024, divisor permite contar tempo
  TCNT2   = 0; //registrador de contagem
  TIMSK2  = 1;//habilita interrupçao do timer2
}

void enviarSerial(int codigo){
  char code[10];
  itoa(codigo, code, 10);
  Serial.print("Enviando ");
  Serial.println(code);
  Wire.beginTransmission(8);
  Wire.write(code);
  Wire.endTransmission();
}

void loop() {
  int i;
  int entradaSerial, entradaSerial2;
  if (trancarEntrada == 0) {
    if (Serial.available()) {
      trancarEntrada = 1;
      entradaSerial = Serial.read() - '0';
      delay(500);
      if (Serial.available()) {
        entradaSerial2 = Serial.read() - '0';
        entradaSerial = concatena(entradaSerial, entradaSerial2);
        Serial.flush();
        Serial.print("Saida solicitada na vaga ");
        Serial.println(entradaSerial);
        //        Serial.print("Retirar: ");
        //        Serial.println(entradaSerial);
      }
//      if (statusSaida == 1) {  // verifica se já foi realizada outra saída
//        statusSaida = 0;    // libera para poder realizar outra saída
//      } else {
 
        trancarEntrada = 1;
        contadorEntrada = 0;
        //statusSaida = 1;         // como é a primeira vez que está passando por aqui pra um mesmo valor, define que já passou e tranca a saída
        saida(entradaSerial);
    }
  }

  if(flagEnvia == 1){
    flagEnvia = 0;
//    Serial.print("Enviando: ");
//    Serial.println(codeGlobal);
    Wire.beginTransmission(8);
    Wire.write(codeGlobal);
    Wire.endTransmission();
    piscaLed(ledPiscante);
  }
  //  delay(500);
  //  entrada(0);
  //  delay(5000);
  //    Wire.beginTransmission(8);
  //    Wire.write(55);
  //    Wire.endTransmission();
  //
  //  delay(5000);
  //  //delay(2000);
  //  //entrada(0);
  //  //delay(2000);
  //
  //  entrada(1);
  //  delay(2000);
  //
  //    Wire.beginTransmission(8);
  //    Wire.write(55);
  //    Wire.endTransmission();
  //    delay(2000);
}

void entrada(int entrada) {   // sul = 1; norte = 0;
  int vagaEscolhida, codeCaminho=0, i, ledVaga;
  for(i=0; i<nSensores; i++)
    digitalWrite(ledEntrada[i], HIGH);      // liga os dois leds indicando entrada trancanda
  Serial.println("-----------------------");
  Serial.println("==== ENTRADA ====");
  if (nCarrosEst < nVagas) {
    Serial.println("Carro permitido!");
    nCarrosEst++;
    if (entrada == 1) {
      vagaEscolhida = buscarVaga(1);    // busca vagas para entrada sul
      Serial.println("Buscando vaga para entrada SUL...");
    } else {
      vagaEscolhida = buscarVaga(0);     // busca vagas para entrada norte
      Serial.println("Buscando vaga para entrada NORTE...");
    }

    
    vagas[vagaEscolhida] = 1;   // indica que a vaga está ocupada
    //ledVaga = definirLedVaga(vagaEscolhida);    // busca a posição do vetor ledVerm correspondente a vaga, conforme o mapa
    Serial.print("Vaga escolhida: ");
    Serial.println(vagaEscolhida);


    codeCaminho = verCode(entrada, vagaEscolhida);    // define o código do caminho com base na entrada e vaga para enviar ao slave
    Serial.print("Código da vaga: ");
    Serial.println(codeCaminho);          
    //enviarSerial(codeCaminho);
    codeGlobal = codeCaminho;
    flagEnvia = 1;
    

    Serial.println("-----------------------");
    ledPiscante = definirLedVaga(vagaEscolhida);
//    piscaLed(ledVerm[ledVaga]);        // inicia a função que piscará o led enquanto a entrada estiver trancada (carro entrando)
  } else {
    Serial.println("Estacionamento lotado!");
    // return -1;
  }
}

int definirLedVaga(int vaga){        // define o led relacionado a vaga conforme o mapa
  if((vaga == 0) || (vaga == 2))
    return 0;
  else if((vaga == 1) || (vaga == 3))
    return 1;
  else if((vaga == 4) || (vaga == 6))
    return 2;     
  else if((vaga == 5) || (vaga == 7))
    return 3;
  else if((vaga == 8) || (vaga == 10))
    return 6;
  else if((vaga == 9) || (vaga == 11))
    return 7;
  else if((vaga == 12) || (vaga == 14))
    return 4;
  else if((vaga == 13) || (vaga == 15))
    return 5;
  else
    return 7;
}

int buscarVaga(int in) {    // escolhe a vaga mais próxima da entrada (caso seja possível)
  int i;
  if (in == 0) {
    for (i = nVagas - 1; i >= 0; i--) { // entrada norte está mais próxima das vagas com maiores números
      if (vagas[i] == 0) {
        return i;
      }
    }
  } else {
    for (i = 0; i < nVagas; i++) { // entrada sul está mais próxima das vagas com menores números
      if (vagas[i] == 0) {
        return i;
      }
    }
  }
}

void saida(int vaga) {     // indica ao vetor de vagas que a vaga foi liberada
  int i;
  for(i=0; i<nSensores; i++)
    digitalWrite(ledEntrada[i], HIGH);      // liga os dois leds indicando entrada trancanda
  Serial.println("-----------------------");
  Serial.println("==== SAIDA ====");
  if ((vaga < 16) && (vaga >= 0)) {
    if (nCarrosEst > 0) {
      if (vagas[vaga] == 1) {
        vagas[vaga] = 0;
        nCarrosEst--;
        digitalWrite(ledVerm[vaga], LOW);
        Serial.print("Carro removido com sucesso da vaga: ");
        Serial.println(vaga);
      } else {
        Serial.print("Vaga ");
        Serial.print(vaga);
        Serial.println(" já está vazia!");
      }
    } else {
      Serial.println("Nenhum carro está estacionado!");
    }
  } else {
    Serial.print("Vaga ");
    Serial.print(vaga);
    Serial.println(" não existe!");
  }
  Serial.println("-----------------------");
}


void piscaLed(int led) {
  int i;
//  Serial.print("Piscando led ");
//  Serial.println(led);
  while(trancarEntrada == 1) {
    digitalWrite(ledVerm[led], HIGH);
    delay(300);
    digitalWrite(ledVerm[led], LOW);
    delay(300);
  }
}


float verDistancia(int sensor) { // 0 - SUL / 1 - NORTE
  //  Serial.print("Trig: ");
  //  Serial.println(echo[sensor]);
  //  Serial.print("Echo: ");
  //  Serial.println(trig[sensor]);
  digitalWrite(trig[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(trig[sensor], LOW);
  float tempo = pulseIn(echo[sensor], HIGH);
  //
  //  Serial.print("Distancia: ");
  //  Serial.print(tempo/29.4/2);
  //  Serial.println("cm");
  return tempo / 29.4 / 2;

}

int concatena(int val1, int val2) {
  char str[2];
  str[0] = val1 + '0';
  str[1] = val2 + '0';
  return atoi(str);
}

int verCode(int entrada, int vaga) { // sul = 1 / norte = 0;
  if (entrada == 0) {      // norte
    switch (vaga) {
      case 0:
        return 27;
        break;
      case 1:
        return 28;
        break;
      case 2:
        return 29;
        break;
      case 3:
        return 30;
        break;
      case 4:
        return 31;
        break;
      case 5:
        return 32;
        break;
      case 6:
        return 33;
        break;
      case 7:
        return 34;
        break;
      case 8:
        return 35;
        break;
      case 9:
        return 36;
        break;
      case 10:
        return 37;
        break;
      case 11:
        return 38;
        break;
      case 12:
        return 39;
        break;
      case 13:
        return 40;
        break;
      case 14:
        return 41;
        break;
      case 15:
        return 42;
        break;
    }
  } else {
    switch (vaga) {
      case 0:
        return 11;
        break;
      case 1:
        return 12;
        break;
      case 2:
        return 13;
        break;
      case 3:
        return 14;
        break;
      case 4:
        return 15;
        break;
      case 5:
        return 16;
        break;
      case 6:
        return 17;
        break;
      case 7:
        return 18;
        break;
      case 8:
        return 19;
        break;
      case 9:
        return 20;
        break;
      case 10:
        return 21;
        break;
      case 11:
        return 22;
        break;
      case 12:
        return 23;
        break;
      case 13:
        return 24;
        break;
      case 14:
        return 25;
        break;
      case 15:
        return 26;
        break;
    }
  }
}

void atualizaLedsLigados(){             // atualiza os leds ligados: para um led estar ligado, as duas vagas correspondentes a ele precisam estar ocupadas
  int i, anterior;
  int *vagasVerif;
  int ledVaga1;
  vagasVerif = (int*)calloc(nVagas, sizeof(int));
  i=0;
  while(i < nVagas){    // faz uma verificação para cada vaga
    if((vagasVerif[i] != 1) && (vagasVerif[i+2] != 1)){       // verifica se ja houve uma verificação para a vaga i
      ledVaga1 = definirLedVaga(i);               
      if((vagas[i] == 1) && (vagas[i+2] == 1)){    // verifica se as duas vagas do led estão ocupadas
        digitalWrite(ledVerm[ledVaga1], HIGH);      // caso as duas estejam ocupadas, liga o led
      }else{
        digitalWrite(ledVerm[ledVaga1], LOW);      // caso uma delas ou as duas estejam livres, desliga o led
      }
      vagasVerif[i] = 1;      // define que a vaga i já foi verificada
      vagasVerif[i+2] = 1;    // define que a vaga i+2 já foi verificada
    }
    i++;
  }
}
