/*
  
  Simon Says! by awdriggs
  
  State change detection (edge detection) from Tom Igoe
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection

  
*/

// this constant won't change:
//attach buttons
const int redButton = 2;
const int blueButton = 4;
const int greenButton = 6;
const int whiteButton = 8;

const int buttonPins[] = { redButton, blueButton, greenButton, whiteButton };

//attch leds
const int redLed = 3;
const int blueLed = 5;  // the pin that the LED is attached to
const int greenLed = 7;
const int whiteLed = 9;

//state of any button?
int currStates[4] = { 0, 0, 0, 0 };  //initialize states to 0
int prevStates[4] = { 0, 0, 0, 0 };

// Variables will change:
int buttonPushCounter = 0;    // counter for the number of button presses
bool buttonState = false;     // current state of the button
int lastButtonState = false;  // previous state of the button

bool playing = true;

int allLights[4] = { redLed, blueLed, greenLed, whiteLed };
const int sequenceLength = 100;
int sequence[sequenceLength];  //get to 100 and you win!
int sequenceIndex = 0;         //keep track of the current index, start at 0
int userIndex = 0;             //keep track of the users inputs. maybe this should go in the checkbuttons
int pause = 500;
int timeLimit = 1000;  //about ?? seconds right now?

void setup() {
  //this could be refactored!
  // initialize the button pin as a input:
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(whiteButton, INPUT);
  // initialize the LED as an output:
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);

  //calculate the entire sequence
  for (int i = 0; i < sequenceLength; i++) {
    int randomIndex = random(0, 4);  //num lights
    Serial.println(randomIndex);
    sequence[i] = allLights[randomIndex];
  }

  // for(int i = 0; i < sequenceLength; i++){
  //   Serial.println(sequence[i]);
  // }

  for (int i = 0; i < 5; i++) {
    flashLights();  //flash all lights on and off at the start, also used for a lose sequence
  }
}


void loop() {

  // // read the pushbutton input pin:
  // buttonState = digitalRead(buttonPin);

  // // compare the buttonState to its previous state
  // if (buttonState != lastButtonState) {
  //   // if the state has changed, increment the counter
  //   if (buttonState == HIGH) {
  //     // if the current state is HIGH then the button went from off to on:
  //     buttonPushCounter++;
  //     Serial.println("on");
  //     Serial.print("number of button pushes: ");
  //     Serial.println(buttonPushCounter);
  //   } else {
  //     // if the current state is LOW then the button went from on to off:
  //     Serial.println("off");
  //   }
  //   // Delay a little bit to avoid bouncing
  //   delay(50);
  // }
  // // save the current state as the last state, for next time through the loop
  // lastButtonState = buttonState;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  // if (buttonPushCounter % 4 == 0) {
  //   digitalWrite(ledPin, HIGH);
  // } else {
  //   digitalWrite(ledPin, LOW);
  // }





  if (playing) {
    Serial.println("start");

    playSequence();
    // Serial.println("end");
    delay(1000);

    Serial.println("user's turn");

    //loop until playing is false, how? either a the time limit is hit or a wrong button is pressed
    bool thisRound = true;
    int timeTaken = 0;  //in seconds
    userIndex = 0;      //reset user index to check a new sequence

    while (thisRound) {
      int buttonPressed = checkButtons();
      if (buttonPressed >= 0) {
        if (buttonPressed + 1 == sequence[userIndex]) {
          Serial.println("correct");
          userIndex++;
          timeTaken = 0;  //reset for next round
        } else {
          Serial.println("incorrect");
          playing = false;
          thisRound = false;
        }
      }
      delay(500);
      timeTaken++;
      Serial.println("waiting");

      if (timeTaken > timeLimit) {
        Serial.println("time is up");
        thisRound = false;
        playing = false;
      }


      //reset time taken? for each correct punch?
    }

    //Serial.println(buttonState);
    //see which button was pressed

    //

    // sequenceIndex++; //keep track of the current index
    // delay(500);
    if (!playing) {
      Serial.println("game over");
    }
  }
}

void flashLights() {
  int flashSequence[4] = { redLed, blueLed, greenLed, whiteLed };

  for (int i = 0; i < 5; i++) {
    digitalWrite(flashSequence[i], HIGH);
  }

  delay(pause);

  for (int i = 0; i < 5; i++) {
    digitalWrite(flashSequence[i], LOW);
  }

  delay(pause);
}

void playSequence() {
  for (int i = 0; i <= sequenceIndex; i++) {
    Serial.println(sequence[i]);
    digitalWrite(sequence[i], HIGH);
    delay(500);
    digitalWrite(sequence[i], LOW);
    delay(500);
  }
}

int checkButtons() {
  for (int i = 0; i < 4; ++i) {  //read the current state of each button
    currStates[i] = digitalRead(buttonPins[i]);
  }

  //Serial.println("checking buttons");
  for (int i = 0; i < 4; i++) {  //check for edges of each button
    if (currStates[i] != prevStates[i]) {
      if (currStates[i] == HIGH) {
        Serial.print("user pressed: ");
        Serial.println(buttonPins[i]);
        digitalWrite(allLights[i], HIGH);  //flash the lights
        delay(250);
        digitalWrite(allLights[i], LOW);

        //update states! needed here?

        return buttonPins[i];  //return the button that was pressed
      }
      // Delay a little bit to avoid bouncing
      //delay(50);
      //return buttonPins[i]; //retun the pin that was pressed?
    }
  }
  // if (currStates != prevStates){
  //   //a butotn was pressed? which one?
  //   Serial.println("button heard!");
  //   for(int i = 0; i < 4; i++){
  //     if(currStates[i] != prevStates[i]){
  //       Serial.println(i);
  //       break;
  //     }
  //   }
  // }

  

  //got to here?
  //delay(10); //for stabiltiy
  return -1;  //no button was pressed
}

void updateStates(){
  //update prevStates
  for (int i = 0; i < 4; i++) {
    prevStates[i] = currStates[i];
  }
}
