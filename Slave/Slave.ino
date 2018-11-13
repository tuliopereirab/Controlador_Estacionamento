#define nLedsVerd 12
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
}
