int *vagas, nCarrosEst=0;
int nVagas = 16;
void setup(){
  Serial.begin(9600);
  vagas = malloc(sizeof(int)*nVagas);
  inicializar();
}

void inicializar(){
  int i;
  for(i=0; i<nVagas; i++){
    vagas[i] = 0; // indica que todas as vagas estão vazias
  }
  Serial.println("Inicializado...");
}

void loop(){
  saida(3);
  delay(1000);
  entrada(1);
  delay(1000);
  entrada(1);
  delay(1000);
}

void entrada(int entrada){    // sul = 1; norte = 0;
  int vagaEscolhida;
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

  Serial.print("Vaga escolhida: ");
  Serial.println(vagaEscolhida);
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
  if(nCarrosEst > 0){
    if(vagas[vaga] == 1){
      vagas[vaga] = 0;
      nCarrosEst--;
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
