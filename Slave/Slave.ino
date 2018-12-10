  #include <Wire.h>
  
  #define  S00 A1
  #define  S01 A2
  #define  S02 2
  #define  S03 3
  #define  S04 4
  #define  S05 5
  #define  S06 6 // #define  S12 6 -> mesma coisa que S06 por causa das ligações da protoboard
  #define  S07 7
  #define  S08 8
  #define  S09 9
  #define  S10 10
  #define  S11 11

///
int flag_testeLed=0, i=0, flag_switch=0, cont=0;
int vet[12] = {11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 40};
//char cod[3];
int estado;
int waiting = 1;


void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  pinMode(S00, OUTPUT);
  pinMode(S01, OUTPUT);
  pinMode(S02, OUTPUT);
  pinMode(S03, OUTPUT);
  pinMode(S04, OUTPUT);
  pinMode(S05, OUTPUT);
  pinMode(S06, OUTPUT);
  pinMode(S07, OUTPUT);
  pinMode(S08, OUTPUT);
  pinMode(S09, OUTPUT);
  pinMode(S10, OUTPUT);
  pinMode(S11, OUTPUT);
    
    Serial.begin(9600);
}

void receiveEvent(int howMany){
  estado = Wire.read();
  waiting = 0;
  Serial.print("Estado recebido: ");
  Serial.println(estado);
  if(estado == 55){
    Serial.println("DESLIGA TUDO!");
    desliga_all();
  }else{
    Serial.println("GERANDO CAMINHO!");
    geraCaminho();
  }
  waiting = 1;
}

void liga_all(){
  
    digitalWrite(S00, HIGH);
    delay(150);
    digitalWrite(S01, HIGH);
    delay(150);
    digitalWrite(S02, HIGH);
    delay(150);
    digitalWrite(S03, HIGH);
    delay(150);
    digitalWrite(S04, HIGH);
    delay(150);
    digitalWrite(S05, HIGH);
    delay(150);
    digitalWrite(S06, HIGH);
    delay(150);
    digitalWrite(S07, HIGH);
    delay(150);
    digitalWrite(S08, HIGH);
    delay(150);
    digitalWrite(S09, HIGH);
    delay(150);
    digitalWrite(S10, HIGH);
    delay(150);
    digitalWrite(S11, HIGH);
    delay(150);
}

void desliga_all(){
  
    digitalWrite(S00, LOW);
    //delay(75);
    digitalWrite(S01, LOW);
    //delay(75);
    digitalWrite(S02, LOW);
    //delay(75);
    digitalWrite(S03, LOW);
    //delay(75);
    digitalWrite(S04, LOW);
    //delay(75);
    digitalWrite(S05, LOW);
    //delay(75);
    digitalWrite(S06, LOW);
    //delay(75);
    digitalWrite(S07, LOW);
    //delay(75);
    digitalWrite(S08, LOW);
    //delay(75);
    digitalWrite(S09, LOW);
    //delay(75);
    digitalWrite(S10, LOW);
    //delay(75);
    digitalWrite(S11, LOW);
    //delay(75);
}

/* void ligaled(int led){  
  digitalWrite(led, HIGH);
  delay(75);
} */

void geraCaminho(){
  switch(estado){
      case 11: // ENTRADA SUL VAGA 0 
        digitalWrite(S00, HIGH);
        break;     
      case 12: // ENTRADA SUL VAGA 1
        digitalWrite(S00, HIGH);
        break;      
      case 13: // ENTRADA SUL VAGA 2
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH); 
        break;      
      case 14: // ENTRADA SUL VAGA 3
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 15: // ENTRADA SUL VAGA 4
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 16: // ENTRADA SUL VAGA 5
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 17: // ENTRADA SUL VAGA 6
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S01, HIGH);
        break;      
      case 18: // ENTRADA SUL VAGA 7
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S01, HIGH);
        break;     
      case 19: // ENTRADA SUL VAGA 8
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 20: // ENTRADA SUL VAGA 9
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 21: // ENTRADA SUL VAGA 10
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S09, HIGH);
        break;     
      case 22: // ENTRADA SUL VAGA 11
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S09, HIGH);
        break;     
      case 23: // ENTRADA SUL VAGA 12
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        break;     
      case 24: // ENTRADA SUL VAGA 13
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        break;     
      case 25: // ENTRADA SUL VAGA 14
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
        break;      
      case 26: // ENTRADA SUL VAGA 15
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
        break;      
      case 27: // ENTRADA NORTE VAGA 0
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
        break;      
      case 28: // ENTRADA NORTE VAGA 1
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
        break;      
      case 29: // ENTRADA NORTE VAGA 2
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 30: // ENTRADA NORTE VAGA 3
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 31: // ENTRADA NORTE VAGA 4
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 32: // ENTRADA NORTE VAGA 5
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 33: // ENTRADA NORTE VAGA 6
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        break;      
      case 34: // ENTRADA NORTE VAGA 7
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        break;      
      case 35: // ENTRADA NORTE VAGA 8
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 36: // ENTRADA NORTE VAGA 9
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;    
      case 37: // ENTRADA NORTE VAGA 10
        digitalWrite(S09, HIGH);
        break;    
      case 38: // ENTRADA NORTE VAGA 11
        digitalWrite(S09, HIGH);
        break;     
      case 39: // ENTRADA NORTE VAGA 12
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        break;     
      case 40: // ENTRADA NORTE VAGA 13
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 41: // ENTRADA NORTE VAGA 14
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;    
      case 42: // ENTRADA NORTE VAGA 15
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;
      default:
        Serial.println("DEFAULT SWITCH");
        break;
    }
}

void teste_leds(){
    if(flag_testeLed == 0){ 
      liga_all();
      delay(500);
      desliga_all();
      delay(500);    
      flag_testeLed = 1;  
      }
}



void loop() {

  if(waiting == 1){
    Serial.println("Aguardando código...");
  }
  delay(500);
  
//teste_leds();  //função que irá ligar e desligar os leds para saber se todos estão ligando e desligando corretamente

 /* 
    if(Serial.available()){   // estrutura para receber os dois valores via comunicação serial
      flag_switch = 1;
      delay(100);  //funciona para garantir que todos os dado foram enviados
        while((Serial.available() && (i<2))){
      cod[i++] = Serial.read();
    }
    cod[i++] = '/0'; 
  } */

 // i=0; // reiniciando posicção do vetor
/*
  if(flag_switch == 1){   // flag necessária para não sobrepor estados e conter redundancias 
  // estado = atoi(cod);    necessário para mudar a string para inteiro 

  Serial.println(estado);  
  geraCaminho(estado);
  } 
  
  flag_switch = 0; // reiniciando a flag switch
  */
  
  //delay(2000);
  
 // desliga_all(); // desligando os leds
//      estado = vet[cont++];
//      Serial.print("Código caminho: ");
//      Serial.println(estado);
//      geraCaminho(estado);
//      if(cont++ > 12){
//      Serial.println("12 possibilidades testadas");
//      cont=0;
//      }
//      delay(2000);
//      desliga_all();
}





/*#define nLedsVerd 12
int *ledVerd;


void setup() {
  Serial.begin(9600);
  ledVerd = malloc(sizeof(int)*nLedsVerd);
  inicializar();
  int i;
  for(i=0; i<nLedsVerd; i++){
    pinMode(ledVerd[i], OUTPUT);
  }
}

void inicializar(){
  inicializarPinos(); 
  int i;
  for(i=0; i<nLedsVerd; i++){
    digitalWrite(ledVerd[i], LOW);
  }
}

void inicializarPinos(){
  ledVerd[0] = A1;
  ledVerd[1] = A2;
  ledVerd[2] = 3;
  ledVerd[3] = 4;
  ledVerd[4] = 5;
  ledVerd[5] = 6;
  ledVerd[6] = 7;
  ledVerd[7] = 8;
  ledVerd[8] = 9;
  ledVerd[9] = 10;
  ledVerd[10] = 11;
  ledVerd[11] = 12;
}

void loop() {
  int i;
  for(i=0; i<nLedsVerd; i++){
    digitalWrite(ledVerd[i], HIGH);
  }
  delay(5000);
  for(i=0; i<nLedsVerd; i++){
    digitalWrite(ledVerd[i], LOW);
  }
  delay(2000);
} */
