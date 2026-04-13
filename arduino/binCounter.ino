// C++ code
//

const int botao = 10;
const int led1 = 2;
const int led2 = 4;
const int led3 = 6;
const int led4 = 8;
int btnState = LOW;

int ledsState[4] = {0, 0, 0, 0};
int ledsOrder[4] = {led4, led3, led2, led1};

int num = 0;

void setup(){
  Serial.begin(9600);
  
  pinMode(botao, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void calcBin(){
  int newNum = num;
  for(int i = 0; i < 4; i++){
    int rest = newNum % 2;
    ledsState[i] = rest;
    newNum = newNum / 2;
  }
}

void updateLeds(){
  for(int i = 0; i < 4; i++){
    digitalWrite(ledsOrder[i], ledsState[i]);
  }
}

void loop(){
  bool currentButtonState = digitalRead(botao);

  if (currentButtonState == HIGH && btnState == LOW) { # sistema de toggle, o sinal só é considerado quando o botão é pressionado e solto
    num++;
    if (num > 15) {
      num = 0;
    }
    calcBin();
    updateLeds();
  }
  btnState = currentButtonState;
}