#define BUTTON 3
#define LED 4
#define DEF 13
#define DELAY 50

unsigned int state = 0;
unsigned int reading = 0;
unsigned int switchState = 0;
unsigned long lastDebounceTime = 0;
void setup(){
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(DEF, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  digitalWrite(DEF,HIGH);
  delay(500);
  switchState = digitalRead(BUTTON);
  digitalWrite(DEF, LOW);
  delay(500);

  switch(state){
   case 0: {
    digitalWrite(LED, LOW);
     if(switchState == HIGH){
       state = 1;
     }
     break;
   }

    case 1: {
      digitalWrite(LED, LOW);
      if(switchState == HIGH){
        state = 1;
      } else {
        state = 2;
      }
      break;
   }

  case 2: {
    digitalWrite(LED, LOW);
    if(switchState == HIGH){
      state = 3;
    } else {
      state = 0;
    }
    break;
  }

  case 3: {
    digitalWrite(LED, HIGH);
    if(switchState == HIGH){
      state = 1;
    } else {
      state = 0;
    }
    break;
  }
  }
}
