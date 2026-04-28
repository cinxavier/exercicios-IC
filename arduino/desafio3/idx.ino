// C++ code
//

int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
int led8 = 9;
int led9 =10;
int btnPin = 11;
int potPin = A0;

long previousMillis = 0; 
const int interval = 300;       
int lastLedOn = 0;

int ledsList[9] = {
  led1,
  led2,
  led3,
  led4,
  led5,
  led6,
  led7,
  led8,
  led9,
};

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);
  pinMode(led9,OUTPUT);
  pinMode(btnPin, INPUT);
  pinMode(potPin,INPUT);
  Serial.begin(9600);
}
int state = LOW;
void pisca(int led){
  if (state == LOW){
  	state = HIGH;
  }else{
    state = LOW;
  }
  digitalWrite(led, state);
}

void selectLed(int ledIdx){
  digitalWrite(ledsList[ledIdx], HIGH);
  ledsList[ledIdx] = 1;
}
int n = 0;
void loop()
{
  int btn = digitalRead(btnPin);
  int pot = analogRead(potPin);

  int ledIdx = map(pot, 0, 1023,0,8);
  
  int led = ledsList[ledIdx];

  if (lastLedOn != led){
    digitalWrite(lastLedOn, LOW);
    lastLedOn = led;
  }
  
  if (millis() - previousMillis >= interval) {
    pisca(led);
    previousMillis = millis(); 
  }
}