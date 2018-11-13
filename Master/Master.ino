#define nLedsVerm 8

int *vagas, nCarrosEst=0;
int nVagas = 16;
int *ledVerm;

void setup(){
  Serial.begin(9600);
  vagas = malloc(sizeof(int)*nVagas);
  ledVerm = malloc(sizeof(int)*nLedsVerm);
  inicializar();
}

void inicializar(){
  int i;
  for(i=0; i<nVagas; i++){
    vagas[i] = 0; // indica que todas as vagas estão vazias
  }
  inicializaLeds();
  for(i=0; i<nLedsVerm; i++){
    digitalWrite(ledVerm[i], LOW);    // desliga todos os leds vermelhos
  }
  Serial.println("Inicializado...");
}

void inicializaLeds(){
  ledVerm[0] = A1;
  ledVerm[1] = A2;
  ledVerm[2] = 3;
  ledVerm[3] = 4;
  ledVerm[4] = 5;
  ledVerm[5] = 6;
  ledVerm[6] = 7;
  ledVerm[7] = 8;
  Serial.println("Pinos dos leds setados...");
}

void loop(){
  int i;
  int entradaSerial;
  if(Serial.available()){
    entradaSerial = Serial.read() - '0';
    Serial.print("Iniciada retirada da vaga ");
    Serial.println(entradaSerial);
    saida(entradaSerial);
  }
  entrada(1);
  delay(2000);
  entrada(0);
  delay(2000);
  entrada(1);
  delay(2000);
}

void entrada(int entrada){    // sul = 1; norte = 0;
  int vagaEscolhida;
  Serial.println("-----------------------");
  Serial.println("==== ENTRADA ====");
  if(nCarrosEst < nVagas){
    Serial.println("Carro permitido!");
    nCarrosEst++;
  }else{
    Serial.println("Estacionamento lotado!");
    return -1;
  }
  if(entrada == 1){
    vagaEscolhida = buscarVaga(1);    // busca vagas para entrada sul
    Serial.println("Buscando vaga para entrada SUL...");
  }else{
    vagaEscolhida = buscarVaga(0);     // busca vagas para entrada norte
    Serial.println("Buscando vaga para entrada NORTE...");
  }

  vagas[vagaEscolhida] = 1;   // indica que a vaga está ocupada
  //piscaLed(ledVerm[vagaEscolhida/2]);
  Serial.println(vagaEscolhida/2);
  digitalWrite(ledVerm[vagaEscolhida/2], HIGH);
  Serial.print("Vaga escolhida: ");
  Serial.println(vagaEscolhida);

  Serial.println("-----------------------");
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
}


void piscaLed(int led){
  int i;
  for(i=0; i<1000; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
  }
}
