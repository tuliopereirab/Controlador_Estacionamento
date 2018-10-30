void setup() {
  Serial.begin(9600);
}

void loop() {
  int i=0;
  char str[15];
  if(Serial.available()){
    while(Serial.available() && i<15){
      str[i++] = Serial.read();
    }
    str[i++] = '\0';
  }
  Serial.println(str);
  delay(1000);
}
