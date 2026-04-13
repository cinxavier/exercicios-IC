int temperatura;

void setup() {
  Serial.begin(9600);
  Serial.println("Digite o valor da temperatura:");
}

void loop() {
  if (Serial.available() > 0) {

    while (Serial.available() == 0);
    temperatura = Serial.parseInt();
    switc
    
  }
}