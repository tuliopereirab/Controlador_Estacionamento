  #include <Wire.h>
  
  #define  S00 A1
  #define  S01 A2
  #define  S02 3
  #define  S03 4
  #define  S04 5
  #define  S05 6
  #define  S06 7 // #define  S12 6 -> mesma coisa que S06 por causa das ligações da protoboard
  #define  S07 8
  #define  S08 9
  #define  S09 10
  #define  S10 11
  #define  S11 12

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
  int x = Wire.read();
  Serial.print("Recebeu ");
  Serial.println(x);
  while(Wire.available()){
    Wire.read();
  }
  gerenciaRecebido(x);
}
void gerenciaRecebido(int x){
  waiting = 0;
  estado = x;
  if(estado == 55){
    Serial.println("DESLIGA TUDO!");
    desliga_all();
    waiting = 1;
  }else{
    Serial.println("GERANDO CAMINHO!");
    geraCaminho();
  }
}

void liga_all(){
  
    digitalWrite(S00, HIGH);
//    Serial.println("s00");
//    delay(5000);
    digitalWrite(S01, HIGH);
//    Serial.println("s01");
//    delay(5000);
    digitalWrite(S02, HIGH);
//    Serial.println("s02");
//    delay(5000);
    digitalWrite(S03, HIGH);
//    Serial.println("s03");
//    delay(5000);
    digitalWrite(S04, HIGH);
//    Serial.println("s04");
//    delay(5000);
    digitalWrite(S05, HIGH);
//    Serial.println("s05");
//    delay(5000);
    digitalWrite(S06, HIGH);
//    Serial.println("s06");
//    delay(5000);
    digitalWrite(S07, HIGH);
//    Serial.println("s07");
//    delay(5000);
    digitalWrite(S08, HIGH);
//    Serial.println("s08");
//    delay(5000);
    digitalWrite(S09, HIGH);
//    Serial.println("s09");
//    delay(5000);
    digitalWrite(S10, HIGH);
//    Serial.println("s10");
//    delay(5000);
    digitalWrite(S11, HIGH);
//    Serial.println("s11");
//    delay(5000);
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
<<<<<<< HEAD
      case 11:       // ENTRADA SUL VAGA 0 - M01
        digitalWrite(S00, HIGH);
        break;     
      case 12:      // ENTRADA SUL VAGA 1 - M02
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH); 
        break;      
<<<<<<< HEAD
      case 14: // ENTRADA SUL VAGA 3
        digitalWrite(S00, HIGH);
=======
      case 11: 			// ENTRADA SUL VAGA 0 - M01
        digitalWrite(S00, HIGH);
        break;     
      case 12: 			// ENTRADA SUL VAGA 1 - M02
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH); 
        break;      
      case 13: 			// ENTRADA SUL VAGA 2 - M01
	digitalWrite(S00, HIGH);

        break;      
      case 14: 			// ENTRADA SUL VAGA 3 - M02
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
=======
      case 13:      // ENTRADA SUL VAGA 2 - M01
  digitalWrite(S00, HIGH);

>>>>>>> Tulio
        break;      
<<<<<<< HEAD
      case 14:      // ENTRADA SUL VAGA 3 - M02
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 15:      // ENTRADA SUL VAGA 4 - M04
        digitalWrite(S00, HIGH);
<<<<<<< HEAD
        digitalWrite(S05, HIGH);
=======
      case 15: 			// ENTRADA SUL VAGA 4 - M04
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S01, HIGH);
        break;      
      case 16: 			// ENTRADA SUL VAGA 5 - M03
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S07, HIGH);
=======
        digitalWrite(S04, HIGH);
        digitalWrite(S01, HIGH);
>>>>>>> Tulio
        break;      
<<<<<<< HEAD
      case 16:      // ENTRADA SUL VAGA 5 - M03
=======
      case 17: 			// ENTRADA SUL VAGA 6 - M04
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S07, HIGH);
        break;      
<<<<<<< HEAD
      case 17:      // ENTRADA SUL VAGA 6 - M04
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S01, HIGH);
        break;      
      case 18:      // ENTRADA SUL VAGA 7 - M03
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 19:      // ENTRADA SUL VAGA 8 - M07
        digitalWrite(S00, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 20:      // ENTRADA SUL VAGA 9 - M08
        digitalWrite(S05, HIGH);
<<<<<<< HEAD
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S09, HIGH);
=======
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
>>>>>>> Tulio
        break;     
      case 21:      // ENTRADA SUL VAGA 10 - M07
        digitalWrite(S00, HIGH);
<<<<<<< HEAD
        digitalWrite(S05, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S09, HIGH);
=======
        digitalWrite(S10, HIGH);
        digitalWrite(S03, HIGH);
>>>>>>> Tulio
        break;     
      case 22:      // ENTRADA SUL VAGA 11 - M08
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
        break;     
      case 23:      // ENTRADA SUL VAGA 12 - M05
=======
      case 18: 			// ENTRADA SUL VAGA 7 - M03
        digitalWrite(S00, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 19: 			// ENTRADA SUL VAGA 8 - M07
        digitalWrite(S00, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S03, HIGH);
        break;      
      case 20: 			// ENTRADA SUL VAGA 9 - M08
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
        break;     
      case 21: 			// ENTRADA SUL VAGA 10 - M07
        digitalWrite(S00, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S03, HIGH);
        break;     
      case 22: 			// ENTRADA SUL VAGA 11 - M08
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
        break;     
      case 23: 			// ENTRADA SUL VAGA 12 - M05
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 24: 			// ENTRADA SUL VAGA 13 - M06
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
        break;     
<<<<<<< HEAD
      case 24:      // ENTRADA SUL VAGA 13 - M06
=======
      case 25: 			// ENTRADA SUL VAGA 14 - M05
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
<<<<<<< HEAD
        break;     
      case 25:      // ENTRADA SUL VAGA 14 - M05
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
        break;      
<<<<<<< HEAD
      case 26: // ENTRADA SUL VAGA 15
        digitalWrite(S00, HIGH);
        digitalWrite(S05, HIGH);
        digitalWrite(S10, HIGH);
        digitalWrite(S11, HIGH);
=======
      case 26:      // ENTRADA SUL VAGA 15 - M06
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
>>>>>>> Tulio
        break;      
      case 27:      // ENTRADA NORTE VAGA 0 - M01
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
        break;      
<<<<<<< HEAD
      case 28: // ENTRADA NORTE VAGA 1
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
=======
        break;      
      case 26: 			// ENTRADA SUL VAGA 15 - M06
        digitalWrite(S05, HIGH);
        digitalWrite(S03, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 27: 			// ENTRADA NORTE VAGA 0 - M01
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
=======
      case 28:      // ENTRADA NORTE VAGA 1 - M02
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);

>>>>>>> Tulio
        break;      
<<<<<<< HEAD
      case 29:      // ENTRADA NORTE VAGA 2 - M01
=======
      case 28: 			// ENTRADA NORTE VAGA 1 - M02
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
<<<<<<< HEAD
        digitalWrite(S03, HIGH);
<<<<<<< HEAD
=======
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
>>>>>>> Tulio
        break;      
      case 30:      // ENTRADA NORTE VAGA 3 - M02
=======

        break;      
      case 29: 			// ENTRADA NORTE VAGA 2 - M01
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S04, HIGH);
        digitalWrite(S00, HIGH);
        break;      
      case 30: 			// ENTRADA NORTE VAGA 3 - M02
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
        break;      
<<<<<<< HEAD
      case 31:      // ENTRADA NORTE VAGA 4 - M04
=======
      case 31: 			// ENTRADA NORTE VAGA 4 - M04
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        break;     
<<<<<<< HEAD
      case 32:      // ENTRADA NORTE VAGA 5 - M03
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 33:      // ENTRADA NORTE VAGA 6 - M04
=======
      case 32: 			// ENTRADA NORTE VAGA 5 - M03
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 33: 			// ENTRADA NORTE VAGA 6 - M04
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S08, HIGH);
        digitalWrite(S02, HIGH);
        digitalWrite(S01, HIGH);
        digitalWrite(S04, HIGH);
        break;      
<<<<<<< HEAD
      case 34:      // ENTRADA NORTE VAGA 7 - M03
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 35:      // ENTRADA NORTE VAGA 8 - M07
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        break;      
      case 36:      // ENTRADA NORTE VAGA 9 - M08
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;    
      case 37:      // ENTRADA NORTE VAGA 10 - M07
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        break;    
      case 38:      // ENTRADA NORTE VAGA 11 - M08
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;     
<<<<<<< HEAD
      case 39: // ENTRADA NORTE VAGA 12
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
=======
      case 39:      // ENTRADA NORTE VAGA 12 - M05
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
>>>>>>> Tulio
        break;     
      case 40:      // ENTRADA NORTE VAGA 13 - M06
        digitalWrite(S09, HIGH);
<<<<<<< HEAD
        digitalWrite(S06, HIGH);
        digitalWrite(S03, HIGH);
=======
>>>>>>> Tulio
        break;      
      case 41:      // ENTRADA NORTE VAGA 14 - M05
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;    
      case 42:      // ENTRADA NORTE VAGA 15 - M06 
=======
      case 34: 			// ENTRADA NORTE VAGA 7 - M03
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;      
      case 35: 			// ENTRADA NORTE VAGA 8 - M07
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        break;      
      case 36: 			// ENTRADA NORTE VAGA 9 - M08
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;    
      case 37: 			// ENTRADA NORTE VAGA 10 - M07
        digitalWrite(S09, HIGH);
        digitalWrite(S06, HIGH);
        break;    
      case 38: 			// ENTRADA NORTE VAGA 11 - M08
        digitalWrite(S09, HIGH);
        digitalWrite(S11, HIGH);
        break;     
      case 39: 			// ENTRADA NORTE VAGA 12 - M05
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;     
      case 40: 			// ENTRADA NORTE VAGA 13 - M06
        digitalWrite(S09, HIGH);
        break;      
      case 41: 			// ENTRADA NORTE VAGA 14 - M05
        digitalWrite(S08, HIGH);
        digitalWrite(S07, HIGH);
        break;    
      case 42: 			// ENTRADA NORTE VAGA 15 - M06 
>>>>>>> 8d033e5921a06aaee9cf377ed0c986816e76b834
        digitalWrite(S09, HIGH);
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


int j=11;
void loop() {
//  liga_all();
//  if(j>42) j=11;
//  estado = j;
//  geraCaminho();
//  j++;
//  Serial.print("Código: ");
//  Serial.println(j);
//  delay(10000);
//  desliga_all();





  if(waiting == 1){
    Serial.println("Aguardando código...");
  }
  delay(800);
//  delay(500);
  
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
