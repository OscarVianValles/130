#define BUTTON 3
#define LED 4
#define DEF 13
#define DELAY 50

unsigned int state = 0;
unsigned int reading = 0;
unsigned int switchState = 0;
unsigned long lastDebounceTime = 0;
bool isOn = false;

void toggle(){
  if(isOn){
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}
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
     if(switchState == HIGH){
       state = 1;
     }
     break;
   }

    case 1: {
      if(switchState == HIGH){
        state = 2;
      } else {
        state = 0;
      }
      break;
   }

  case 2: {
    if(switchState == HIGH){
      state = 3;
    } else {
      state = 0;
    }
    break;
  }

  case 3: {
    toggle();
    if(switchState == HIGH){
      state = 1;
    } else {
      state = 0;
    }
    break;
  }
  }
}
