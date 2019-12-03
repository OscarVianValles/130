// Defining Pins
#define OFF 14
#define VEND_15 13
#define VEND_10 12
#define VEND_05 11
#define CHANGE_10 10
#define CHANGE_05 9
#define CURRENT_15 8
#define CURRENT_10 7
#define CURRENT_05 6
#define SWITCH 5
#define COIN_10 A0
#define COIN_05 A1
#define CHOICE_15 A2
#define CHOICE_10 A3
#define CHOICE_05 A4

// Saving current states
unsigned int currentState = 0;

// Button States
bool isRunning = false;
bool isCoin10Pressed = false;
bool isCoin05Pressed = false;
bool isChoice15Pressed = false;
bool isChoice10Pressed = false;
bool isChoice05Pressed = false;

// Last Pressed Lengths
unsigned long coin10LastPressedTime = 0;
unsigned long coin05LastPressedTime = 0;
unsigned long choice15LastPressedTime = 0;
unsigned long choice10LastPressedTime = 0;
unsigned long choice05LastPressedTime = 0;

// Debounce delay
unsigned long debounceDelay = 100;


void changeVendOutput(int choice){
  switch(choice){
    case VEND_15:
      digitalWrite(VEND_15, HIGH);
      digitalWrite(VEND_10, LOW);
      digitalWrite(VEND_05, LOW);
      break;

    case VEND_10:
      digitalWrite(VEND_15, LOW);
      digitalWrite(VEND_10, HIGH);
      digitalWrite(VEND_05, LOW);
      break;

    case VEND_05:
      digitalWrite(VEND_15, LOW);
      digitalWrite(VEND_10, LOW);
      digitalWrite(VEND_05, HIGH);
      break;

    default:
      digitalWrite(VEND_15, LOW);
      digitalWrite(VEND_10, LOW);
      digitalWrite(VEND_05, LOW);
      break;
  }
}

void changeChangeOutput(int choice){
  switch(choice){
    case CHANGE_10:
      digitalWrite(CHANGE_10, HIGH);
      digitalWrite(CHANGE_05, LOW);
      break;

    case CHANGE_05:
      digitalWrite(CHANGE_10, LOW);
      digitalWrite(CHANGE_05, HIGH);
      break;

    default:
      digitalWrite(CHANGE_10, LOW);
      digitalWrite(CHANGE_05, LOW);
      break;
  }
}

void changeCurrentOutput(int choice){
  switch(choice){
    case CURRENT_15:
      digitalWrite(CURRENT_15, HIGH);
      digitalWrite(CURRENT_10, LOW);
      digitalWrite(CURRENT_05, LOW);
      break;

    case CURRENT_10:
      digitalWrite(CURRENT_15, LOW);
      digitalWrite(CURRENT_10, HIGH);
      digitalWrite(CURRENT_05, LOW);
      break;

    case CURRENT_05:
      digitalWrite(CURRENT_15, LOW);
      digitalWrite(CURRENT_10, LOW);
      digitalWrite(CURRENT_05, HIGH);
      break;

    default:
      digitalWrite(CURRENT_15, LOW);
      digitalWrite(CURRENT_10, LOW);
      digitalWrite(CURRENT_05, LOW);
      break;
  }
}

void setup(){
  // Setup LED pins
  pinMode(VEND_15, OUTPUT);
  pinMode(VEND_10, OUTPUT);
  pinMode(VEND_05, OUTPUT);
  pinMode(CHANGE_10, OUTPUT);
  pinMode(CHANGE_05, OUTPUT);
  pinMode(CURRENT_15, OUTPUT);
  pinMode(CURRENT_10, OUTPUT);
  pinMode(CURRENT_05, OUTPUT);

  // Setup Switch Pin
  pinMode(SWITCH, INPUT_PULLUP);

  // Setup Buttons
  pinMode(COIN_10, INPUT);
  pinMode(COIN_05, INPUT);
  pinMode(CHOICE_15, INPUT);
  pinMode(CHOICE_10, INPUT);
  pinMode(CHOICE_05, INPUT);

  // Turn off all LEDs
  changeVendOutput(OFF);
  changeChangeOutput(OFF);
  changeCurrentOutput(OFF);

  // Begin Serial Messaging
  Serial.begin(9600);
}

void loop(){
  int switchState = !digitalRead(SWITCH);
  Serial.println(currentState);

  // Set the correct state if switch is toggled, if toggled, then the states
  // will start being run, else, a boolean value will be set to false which will
  // be used in the last states to check which state to go to next
  if (switchState == 1){
    isRunning = true;
    if (currentState == 0){
      currentState = 1;
    }
  } else {
    isRunning = false;
  }

  // Getting and Debouncing all inputs

  //Coin 10
  if(digitalRead(COIN_10) == 1 && !isCoin10Pressed){
    if((millis() - coin10LastPressedTime) > debounceDelay){
      isCoin10Pressed = true;
      coin10LastPressedTime = millis();
    }
  } else if (digitalRead(COIN_10) == 0 && isCoin10Pressed){
    isCoin10Pressed = false;
  }

  // Coin 05
  if(digitalRead(COIN_05) == 1 && !isCoin05Pressed){
    if((millis() - coin05LastPressedTime) > debounceDelay){
      isCoin05Pressed = true;
      coin05LastPressedTime = millis();
    }
  } else if (digitalRead(COIN_05) == 0 && isCoin05Pressed){
    isCoin05Pressed = false;
  }

  // Choice 15
  if(digitalRead(CHOICE_15) == 1 && !isChoice15Pressed){
    if((millis() - choice15LastPressedTime) > debounceDelay){
      isChoice15Pressed = true;
      choice15LastPressedTime = millis();
    }
  } else if (digitalRead(CHOICE_15) == 0 && isChoice15Pressed){
    isChoice15Pressed = false;
  }

  // Choice 10
  if(digitalRead(CHOICE_10) == 1 && !isChoice10Pressed){
    if((millis() - choice10LastPressedTime) > debounceDelay){
      isChoice10Pressed = true;
      choice10LastPressedTime = millis();
    }
  } else if (digitalRead(CHOICE_10) == 0 && isChoice10Pressed){
    isChoice10Pressed = false;
  }

  // Choice 05
  if(digitalRead(CHOICE_05) == 1 && !isChoice05Pressed){
    if((millis() - choice05LastPressedTime) > debounceDelay){
      isChoice05Pressed = true;
      choice05LastPressedTime = millis();
    }
  } else if (digitalRead(CHOICE_05) == 0 && isChoice05Pressed){
    isChoice05Pressed = false;
  }

  // Start States
  switch(currentState){
    case 0:
      changeVendOutput(OFF);
      changeChangeOutput(OFF);
      changeCurrentOutput(OFF);
      break;

    case 1:
      changeVendOutput(OFF);
      changeChangeOutput(OFF);
      changeCurrentOutput(OFF);

      if(isCoin05Pressed){
        currentState = 2;
      } else if (isCoin10Pressed){
        currentState = 3;
      }

      break;

    // 5 Pesos Current
    case 2:
      changeVendOutput(OFF);
      changeChangeOutput(OFF);
      changeCurrentOutput(CURRENT_05);

      if(isCoin05Pressed){
        currentState = 3;
      } else if(isCoin10Pressed){
        currentState = 4;
      } else if(isChoice05Pressed){
        currentState = 5;
      }

      break;

    // 10 Pesos Current
    case 3:
      changeVendOutput(OFF);
      changeChangeOutput(OFF);
      changeCurrentOutput(CURRENT_10);

      if(isCoin10Pressed){
        currentState = 11;
      } else if(isCoin05Pressed){
        currentState = 4;
      } else if(isChoice10Pressed){
        currentState = 9;
      } else if(isChoice05Pressed){
        currentState = 10;
      }

      break;

    case 4:
      changeVendOutput(OFF);
      changeChangeOutput(OFF);
      changeCurrentOutput(CURRENT_15);

      if(isCoin05Pressed){
        currentState = 12;
      } else if(isCoin10Pressed){
        currentState = 13;
      } else if(isChoice15Pressed){
        currentState = 6;
      } else if(isChoice10Pressed){
        currentState = 7;
      } else if (isChoice05Pressed){
        currentState = 8;
      }

      break;

    case 5:
      changeVendOutput(VEND_05);
      changeChangeOutput(OFF);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;


    case 6:
      changeVendOutput(VEND_15);
      changeChangeOutput(OFF);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;

    case 7:
      changeVendOutput(VEND_10);
      changeChangeOutput(CHANGE_05);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;

    case 8:
      changeVendOutput(VEND_05);
      changeChangeOutput(CHANGE_10);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;

    case 9:
      changeVendOutput(VEND_10);
      changeChangeOutput(OFF);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;

    case 10:
      changeVendOutput(VEND_05);
      changeChangeOutput(CHANGE_05);
      changeCurrentOutput(OFF);
      delay(1500);

      if(isRunning){
        currentState = 1;
      } else {
        currentState = 0;
      }

      break;

    case 11:
      changeVendOutput(OFF);
      changeChangeOutput(CHANGE_10);
      changeCurrentOutput(CURRENT_10);
      delay(1500);

      currentState = 3;
      break;

    case 12:
      changeVendOutput(OFF);
      changeChangeOutput(CHANGE_05);
      changeCurrentOutput(CURRENT_15);
      delay(1500);

      currentState = 4;
      break;

    case 13:
      changeVendOutput(OFF);
      changeChangeOutput(CHANGE_10);
      changeCurrentOutput(CURRENT_15);
      delay(1500);

      currentState = 4;
      break;
    default:
      break;
  }

  isCoin10Pressed = false;
  isCoin05Pressed = false;
  isChoice15Pressed = false;
  isChoice10Pressed = false;
  isChoice05Pressed = false;

  delay(10);
}
