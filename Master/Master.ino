#include <Wire.h>

#define nLedsVerm 8
#define nSensores 2

int *vagas, nCarrosEst=0;
int nVagas = 16;
int *ledVerm;
int *trig, *echo;

int trancarEntrada = 0;   // evita duas entradas simultâneas (uma em cada sensor);
int contadorEntrada=1000;    // conta o tempo entre uma entrada e a liberação para a próxima
int contador = 0;         // conta o tempo de verificação dos sensores
int statusSaida = 0;      // evita que sejam feitas duas chamadas da função saída quando for digitado um valor qualquer (tranca e depois libera)


ISR(TIMER1_OVF_vect){     // conta o tempo necessário para entrada e libera a entrada após esse tempo
  contadorEntrada++;
  if(contadorEntrada == 500){
    Wire.beginTransmission(8);
    Wire.write(55);
    Wire.endTransmission();
    Serial.println("Entrada liberada!");
    trancarEntrada = 0;
  }
}

ISR(TIMER2_OVF_vect){    // verifica os sensores a cada período de tempo
  float distancia;
  TCNT2 = 0;
  contador++;
  if(contador == 20){
    distancia = verDistancia(0);  // verificação NORTE
    Serial.print("Distancia Norte: ");
    Serial.println(distancia);
    if((distancia < 7) && (trancarEntrada == 0)){  // verifica presença de algum carro e se já existe uma entrada em andamento
      Serial.println("Entrada Norte!");
      trancarEntrada = 1;     // tranca a entrada enquanto se passa o tempo de entrada de 1 carro
      contadorEntrada = 0;     // inicia a contar o tempo no Timer entrada
      //entrada(0);
    }//else Serial.println("Sem entrada SUL.");
    
    distancia = verDistancia(1);  // verificação SUL
    Serial.print("Distancia Sul: ");
    Serial.println(distancia);
    if((distancia < 7) && (trancarEntrada == 0)){
      Serial.println("Entrada Sul!");
      trancarEntrada = 1;   // tranca a entrada enquanto se passa o tempo de entrada de 1 carro
      contadorEntrada = 0;     // inicia a contar o tempo no Timer entrada
      entrada(1);
    }//else Serial.println("Sem entrada NORTE.");
    contador = 0;
  }
}


void setup(){
  Wire.begin();
  Serial.begin(9600);
  vagas = (int*)malloc(sizeof(int)*nVagas);         // aloca o número de vagas
  ledVerm = (int*)malloc(sizeof(int)*nLedsVerm);   // aloca o vetor de leds vermelhos
  trig = (int*)malloc(sizeof(int)*nSensores);
  echo = (int*)malloc(sizeof(int)*nSensores);
  inicializar();       // inicializa vagas vazias e leds apagados, assim como os pinos de cada led. Inicializa também os TIMERS
  int i;
  for(i=0; i<nLedsVerm; i++){
    pinMode(ledVerm[i], OUTPUT);   // inicializa os leds vermelhos
  }
  for(i=0; i<nSensores; i++){
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
  
}

void inicializar(){
  int i;
  for(i=0; i<nVagas; i++){
    vagas[i] = 0; // indica que todas as vagas estão vazias
  }
  inicializaLeds();
  inicializaSensores();
  inicializaTimers();
  for(i=0; i<nLedsVerm; i++){
    digitalWrite(ledVerm[i], LOW);    // desliga todos os leds vermelhos
  }
  Serial.println("Inicializado...");
}

void inicializaLeds(){     // mapeamento dos pinos dos LEDS
  ledVerm[0] = A1;
  ledVerm[1] = A2;
  ledVerm[2] = 3;
  ledVerm[3] = 2;
  ledVerm[4] = 5;
  ledVerm[5] = 6;
  ledVerm[6] = 7;
  ledVerm[7] = 8;
  Serial.println("Pinos dos leds setados...");
}

void inicializaSensores(){
  trig[0] = 12; // norte
  trig[1] = 10; // sul

  echo[0] = 11; // norte
  echo[1] = 9; // sul
}

void inicializaTimers(){
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

void loop(){
  int i;
  int entradaSerial, entradaSerial2;
  if(trancarEntrada == 0){
    if(Serial.available()){
      entradaSerial = Serial.read() - '0';
      if(Serial.available()){
        entradaSerial2 = Serial.read() - '0';
        entradaSerial = concatena(entradaSerial, entradaSerial2);
        Serial.flush();
//        Serial.print("Retirar: ");
//        Serial.println(entradaSerial);
      }
      if(statusSaida == 1){    // verifica se já foi realizada outra saída
        statusSaida = 0;    // libera para poder realizar outra saída
      }else{
        trancarEntrada = 1;
        contadorEntrada = 0;
        statusSaida = 1;         // como é a primeira vez que está passando por aqui pra um mesmo valor, define que já passou e tranca a saída
        saida(entradaSerial);
      }
    }
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

void entrada(int entrada){    // sul = 1; norte = 0;
  int vagaEscolhida, codeCaminho;
  Serial.println("-----------------------");
  Serial.println("==== ENTRADA ====");
  if(nCarrosEst < nVagas){
    Serial.println("Carro permitido!");
    nCarrosEst++;
    if(entrada == 1){
      vagaEscolhida = buscarVaga(1);    // busca vagas para entrada sul
      Serial.println("Buscando vaga para entrada SUL...");
    }else{
      vagaEscolhida = buscarVaga(0);     // busca vagas para entrada norte
      Serial.println("Buscando vaga para entrada NORTE...");
    }
  
    vagas[vagaEscolhida] = 1;   // indica que a vaga está ocupada
    //piscaLed(ledVerm[vagaEscolhida/2]);
    //Serial.println(vagaEscolhida/2);
    digitalWrite(ledVerm[vagaEscolhida/2], HIGH);
    Serial.print("Vaga escolhida: ");
    Serial.println(vagaEscolhida);

    
    codeCaminho = verCode(entrada, vagaEscolhida);    // define o código do caminho com base na entrada e vaga para enviar ao slave
    Wire.beginTransmission(8);          // envia o código ao slave
    Wire.write(codeCaminho);
    Wire.endTransmission();

    
    Serial.println("-----------------------");
  }else{
    Serial.println("Estacionamento lotado!");
   // return -1;
  }
}

int buscarVaga(int in){     // escolhe a vaga mais próxima da entrada (caso seja possível)
  int i;
  if(in == 0){
    for(i=nVagas-1; i>=0; i--){     // entrada norte está mais próxima das vagas com maiores números
      if(vagas[i] == 0){
        return i;
      }
    }
  }else{
    for(i=0; i<nVagas; i++){     // entrada sul está mais próxima das vagas com menores números
      if(vagas[i] == 0){
        return i;
      }
    }
  }
}

void saida(int vaga){      // indica ao vetor de vagas que a vaga foi liberada
  Serial.println("-----------------------");
  Serial.println("==== SAIDA ====");
  if((vaga < 16) && (vaga >= 0)){
    if(nCarrosEst > 0){
      if(vagas[vaga] == 1){
        vagas[vaga] = 0;
        nCarrosEst--;
        digitalWrite(ledVerm[vaga], LOW);
        Serial.print("Carro removido com sucesso da vaga: ");
        Serial.println(vaga);
      }else{
        Serial.print("Vaga ");
        Serial.print(vaga);
        Serial.println(" já está vazia!"); 
      }
    }else{
      Serial.println("Nenhum carro está estacionado!");
    }
  }else{
    Serial.println("Vaga não existe!");
  }
  Serial.println("-----------------------");
}


void piscaLed(int led){
  int i;
  for(i=0; i<1000; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
  }
}


float verDistancia(int sensor){ // 0 - SUL / 1 - NORTE
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
  return tempo/29.4/2; 
  
}

int concatena(int val1, int val2){
  char str[2];
  str[0] = val1 + '0';
  str[1] = val2 + '0';
  return atoi(str);
}

int verCode(int entrada, int vaga){ // sul = 1 / norte = 0;
  if(entrada == 0){        // norte
    switch(vaga){
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
  }else{
    switch(vaga){
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
