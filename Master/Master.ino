void setup(){
  Serial.begin(9600);
}

void loop(){
  char str[10] = "Dudi lixo";
  Serial.write(str);
  Serial.println("Enviado!");
  delay(1000);
  
}
