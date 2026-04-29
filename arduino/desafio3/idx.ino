int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
int led8 = 9;
int led9 = 10;
int btnPin = 11;
int potPin = A0;
int lastLedOn = led1;

int ledsListBackup[3][3] = {
  {led1, led2, led3},
  {led4, led5, led6},
  {led7, led8, led9},
};
int ledsList[3][3] = {
  {led1, led2, led3},
  {led4, led5, led6},
  {led7, led8, led9},
};

bool gameFinished = false;


int ledState = LOW;
void blink(int led){
  ledState =! ledState;
  digitalWrite(led, ledState);
}

bool checkXY(char direction){
  short points = 0;  

  for(short l = 0; l<3; l++){
    for(short c = 0; c< 3;c++){
      short line = l;
      short column = c;

      if (direction == 'v'){
        short holder;
        holder = line;
        line = column;
        column = holder;
      }

      if (ledsList[line][column] != 0){
        points = 0;
        break;
      }
      points++;
    }
    if (points == 3){
      return true;
    }
  }
  return false;
}

bool checkDiagonals(){
  short points = 0;
  for (short i = 0;i<3;i++){
    if(ledsList[i][i] != 0){
      points = 0;
      break;
    }
    points++;
  }

  if(points == 3){
    return true;
  }

  for (short i = 2;i>-1;i--){
    if(ledsList[(i-2)*-1][i] != 0){
      points = 0;
      break;
    }
    points++;
  }

  if (points == 3){
    return true;
  }
  else{
    return false;
  }
}

void turnAllOff(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);

}

void resetGame(){
  turnAllOff();
  for (short l = 0; l< 3; l++){
    for (short c = 0; c< 3; c++){
      ledsList[l][c] = ledsListBackup[l][c];
    }
  }
  gameFinished = false;
  
}


void setup(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(btnPin, INPUT);
  Serial.begin(9600);
}

int interval = 200;
unsigned long int lastInterval = 0;
void loop(){
  if(!gameFinished){

    int potVal = analogRead(potPin);
    int btnVal = digitalRead(btnPin);

    int ledIdx = map(potVal, 0, 1023, 0,8);
    int led = ledsList[ledIdx/3][ledIdx%3];

    if(btnVal == 1){
      digitalWrite(led, HIGH);
      ledsList[ledIdx/3][ledIdx%3] = 0;
      
      gameFinished = checkXY('h');
      if (!gameFinished){
        gameFinished = checkXY('v');
      }
      if(!gameFinished){
        gameFinished = checkDiagonals();
      }
    }
    
    if (lastLedOn != led){
      if (led != 0){
        digitalWrite(lastLedOn, LOW); 
      }
      lastLedOn = led;
    }
  
    if (millis() - lastInterval >= interval){
      blink(led);
      lastInterval = millis();
    }
    
  }else{
    delay(400);
    resetGame();
  
  
}
}
