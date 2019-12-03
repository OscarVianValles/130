// Defining Pins
#define SWITCH 4
#define BUTTON 3
#define CAR_GREEN 13
#define CAR_YELLOW 12
#define CAR_RED 11
#define PED_GREEN 9
#define PED_RED 10
#define REQUEST 8

// Helper definitions for change colors
#define GREEN 1
#define YELLOW 2
#define RED 3
#define OFF 10

// Setting variables
int switchState = 0;
int oldSwitchState = 0;
int buttonState = 0;

bool running = false;
bool initialTimeSet = false;
bool initialBlinkTimeSet = false;
bool buttonPress = false;

unsigned long time = 0;
unsigned long initialTime = 0;
unsigned long currentTime = 0;
unsigned long initialBlinkTime = 0;
unsigned long blinkTime = 0;
unsigned long debounce = 200UL;

unsigned int currentState = 0;

void changeCarColor(int choice){
  switch(choice){
    case 1:
      digitalWrite(CAR_GREEN, HIGH);
      digitalWrite(CAR_YELLOW, LOW);
      digitalWrite(CAR_RED, LOW);
      break;

    case 2:
      digitalWrite(CAR_GREEN, LOW);
      digitalWrite(CAR_YELLOW, HIGH);
      digitalWrite(CAR_RED, LOW);
      break;

    case 3:
      digitalWrite(CAR_GREEN, LOW);
      digitalWrite(CAR_YELLOW, LOW);
      digitalWrite(CAR_RED, HIGH);
      break;

    default:
      digitalWrite(CAR_GREEN, LOW);
      digitalWrite(CAR_YELLOW, LOW);
      digitalWrite(CAR_RED, LOW);
      break;
  }
}

void changePedColor(int choice){
  switch(choice){
    case 1:
      digitalWrite(PED_GREEN, HIGH);
      digitalWrite(PED_RED, LOW);
      break;
    case 3:
      digitalWrite(PED_GREEN, LOW);
      digitalWrite(PED_RED, HIGH);
      break;
    default:
      digitalWrite(PED_GREEN, LOW);
      digitalWrite(PED_RED, LOW);
  }
}

void setup()
{

  // Setup Pins
  pinMode(SWITCH, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(REQUEST, OUTPUT);

  // Turn off all leds
  changePedColor(OFF);
  changeCarColor(OFF);


  // Begin serial messaging
  Serial.begin(9600);
}


void loop()
{
  // Turn on request LED if requested
  if(buttonPress){
    digitalWrite(REQUEST, HIGH);
  } else {
    digitalWrite(REQUEST, LOW);
  }

  // Read current state of the switch
  int switchState = digitalRead(SWITCH);

  if(switchState && !oldSwitchState && millis() - time > debounce){
    running = !running;
    time = millis();
  }

  oldSwitchState = switchState;

  if (running){
    if(currentState == 0 || currentState == 7){
      currentState = 1;
    }
  } else {
    if(currentState == 7){
      currentState = 7;
    } else {
      currentState = 0;
    }
  }

  // STATE 0
  switch(currentState){
  case 0: {
    if (!initialBlinkTimeSet){
      initialBlinkTime = millis();
      initialBlinkTimeSet = true;
    }


    changePedColor(OFF);
    changeCarColor(OFF);

    blinkTime = millis() - initialBlinkTime;
    if(blinkTime >= 500){
      currentState = 7;
      initialBlinkTimeSet = false;
    }
    break;
  }

  case 7: {
    if (!initialBlinkTimeSet){
      initialBlinkTime = millis();
      initialBlinkTimeSet = true;
    }

    changePedColor(RED);
    changeCarColor(YELLOW);

    blinkTime = millis() - initialBlinkTime;
    if(blinkTime >= 500){
      currentState = 0;
      initialBlinkTimeSet = false;
    }
    break;
  }

  // STATE 1 - CARS GO
  case 1: {
    changePedColor(RED);
    changeCarColor(GREEN);
    if(digitalRead(BUTTON) == 1){
      currentState = 2;
    }
    break;
  }

  // STATE 2 - CARS WARNING
  case 2: {
    if (!initialTimeSet){
      initialTime = millis();
      initialTimeSet = true;
    }

    changePedColor(RED);
    changeCarColor(YELLOW);
    buttonPress = true;

    currentTime = millis() - initialTime;
    if(currentTime >= 5000){
      currentState = 3;
      initialTimeSet = false;
      buttonPress = false;
    }
    break;
  }

  // STATE 3 - GO PED
  case 3: {
    if (!initialTimeSet){
      initialTime = millis();
      initialTimeSet = true;
    }

    changePedColor(GREEN);
    changeCarColor(RED);

    currentTime = millis() - initialTime;
    if(currentTime >= 10000){
      currentState = 4;
      initialTimeSet = false;
    }
    break;
  }

  // STATE 4 - BLINK OFF
  case 4: {
    if (!initialTimeSet){
      initialTime = millis();
      initialTimeSet = true;
    }

    if (!initialBlinkTimeSet){
      initialBlinkTime = millis();
      initialBlinkTimeSet = true;
    }

    changePedColor(OFF);
    changeCarColor(RED);

    if(digitalRead(BUTTON) == 1){
      buttonPress = true;
    }

    blinkTime = millis() - initialBlinkTime;
    if(blinkTime >= 500){
      currentState = 5;
      initialBlinkTimeSet = false;
    }
    break;
  }

  case 5: {
    if (!initialBlinkTimeSet){
      initialBlinkTime = millis();
      initialBlinkTimeSet = true;
    }

    changePedColor(GREEN);
    changeCarColor(RED);

    if(digitalRead(BUTTON) == 1){
      buttonPress = true;
    }

    currentTime = millis() - initialTime;
    if(currentTime >= 5000){
      currentState = 6;
      initialTimeSet = false;
      initialBlinkTimeSet = false;
    }

    blinkTime = millis() - initialBlinkTime;
    if(blinkTime >= 500){
      currentState = 4;
      initialBlinkTimeSet = false;
    }
    break;
  }

  case 6: {
    if(!initialTimeSet){
      initialTime = millis();
      initialTimeSet = true;
    }

    changePedColor(RED);
    changeCarColor(GREEN);

    if(digitalRead(BUTTON) == 1){
      buttonPress = true;
    }

    currentTime = millis() - initialTime;
    if(currentTime >= 15000){
      if(buttonPress){
        currentState = 2;
        initialTimeSet = false;
        buttonPress = false;
      } else {
        currentState = 1;
        initialTimeSet = false;
      }
    }
    break;
  }
  }


  delay(10); // Delay a little bit to improve simulation performance
}
