/*
  Simon Says! by awdriggs
  
  State change detection (edge detection) from Tom Igoe
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection

  chatgpt helped write the loop to check all the buttons

  need to write the win condition
*/

// this constant won't change:
//attach buttons, 
//REFACTOR this could be abstracted some into an array
const int redButton = 2;
const int blueButton = 4;
const int greenButton = 6;
const int whiteButton = 8;

const int buttonPins[] = { redButton, blueButton, greenButton, whiteButton };

//attch leds
//REFACTOR could also be abstracted some
const int redLed = 3;
const int blueLed = 5;  // the pin that the LED is attached to
const int greenLed = 7;
const int whiteLed = 9;



//button states
int currStates[4] = { 0, 0, 0, 0 };  //initialize states to 0
int prevStates[4] = { 0, 0, 0, 0 };

bool playing = true;

int allLights[4] = { redLed, blueLed, greenLed, whiteLed };
const int sequenceLength = 100;
int sequence[sequenceLength];  //get to 100 and you win! need to write a win condition!
int sequenceIndex = 0;         //keep track of the current index, start at 0
int userIndex = 0;             //keep track of the users inputs. maybe this should go in the checkbuttons
int pause = 500;
int timeLimit = 100;  //about 100 * 50 = 5000 seconds right now?

//notes
int notes[]= {261, 329, 392, 440};

void setup() {
  // initialize the button pin as a input:
  // REFACTOR could put this in a loop
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
  //TODO add a random seed
  for (int i = 0; i < sequenceLength; i++) {
    int randomIndex = random(0, 4);  //num lights
    Serial.println(randomIndex);
    sequence[i] = allLights[randomIndex];
  }

  //flash the lights a few times, to get started
  for (int i = 0; i < 3; i++) {
    flashLights();  //flash all lights on and off at the start, also used for a lose sequence
  }
}

void loop() {

  if (playing) { //check to see if you are playing
    Serial.println("start");

    delay(1000);
    playSequence();
    // Serial.println("end");
    //delay(100);

    Serial.println("user's turn");

    //loop until playing is false, how? either a the time limit is hit or a wrong button is pressed
    int timeTaken = 0;  //in loops
    userIndex = 0;      //reset user index to check a new sequence
    
    while (true) { //repeats until a false button is pressed or the users has keyed in the whole sequence
      int buttonPressed = checkButtons(); //returns the button pin or -1 if no checked buttons are pressed
      if (buttonPressed >= 0) { //heard a button!
        if (buttonPressed + 1 == sequence[userIndex]) { //check to see if the button matches the light, light is always one more than the button pin
          Serial.println("correct");
          timeTaken = 0;  //reset for next round

          //users has the whole sequence correct!
          if(userIndex == sequenceIndex){
            sequenceIndex++; //increase the sequence count
            break; //break out of the while loop and play
          } else {
            userIndex++; //button was right so move to the next light in sequence
            continue; //repeat the while loop
          }
        } else {
          Serial.println("incorrect");
          playing = false; //set playing to false
          break;
          //thisRound = false;
        }
      }
      Serial.println("waiting");
      delay(50); //delay to give the user time, this could increase to make the game harder
      timeTaken++;
      

      if (timeTaken > timeLimit) {
        Serial.println("time is up");
        playing = false; 
        break; //time is up so end the game
      }
    }
    
    //game is over
    if (!playing) {
      Serial.println("game over");
      //play end sounds
    }
  }
}

void flashLights() {
  int flashSequence[4] = { redLed, blueLed, greenLed, whiteLed };

  for (int i = 0; i < 5; i++) {
    digitalWrite(flashSequence[i], HIGH);
    tone(12, notes[i], pause);
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
    // Serial.print("pin index");
    int noteIndex = getNote(sequence[i]);
    // Serial.println(index);    
    tone(12, notes[noteIndex], 500); //sequence index
    Serial.print("sequence note ");
    Serial.println(notes[i]);
    delay(pause);
    digitalWrite(sequence[i], LOW);
    delay(pause);
  }
}

int checkButtons() {
  updateStates(); //update before checking new states

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
        tone(12, notes[i], pause);
        Serial.print("note");
        Serial.println(notes[i]);
        delay(pause);
        digitalWrite(allLights[i], LOW);

        //update states! needed here?
        
        return buttonPins[i];  //return the button that was pressed
      }
      // Delay a little bit to avoid bouncing
      //delay(50);
      //return buttonPins[i]; //return the pin that was pressed?
    }
  }
  
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

int getNote(int pin){
  Serial.print("pin passed to index of");
  Serial.println(pin);
  
  for(int a = 0; a < 4; a++){
    // Serial.print("all lights ");
    // Serial.print(a);
    // Serial.println(allLights[a]);
    // Serial.println(allLights[a]);
    if(allLights[a] == pin){
      return a;
    } 
  }
  return -1;
}