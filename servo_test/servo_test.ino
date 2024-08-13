/* Sweep
   by BARRAGAN <http://barraganstudio.com>
   This example code is in the public domain.

   modified 8 Nov 2013
   by Scott Fitzgerald
https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
 */

#include <Servo.h>

Servo myservo;  // create Servo object to control a servo
                // twelve Servo objects can be created on most boards

int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };


/* int pos = 0;    // variable to store the servo position */
int inByte = 0;        // incoming serial byte
int readingData[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // serial business
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  establishContact();  // send a byte to establish contact until receiver responds

  // i/o business
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  for (int i = 0; i < 8; i++) {
    pinMode(analogPins[i], INPUT);
  }
}


void loop() {
  /* for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees */
  /*   // in steps of 1 degree */
  /*   myservo.write(pos);              // tell servo to go to position in variable 'pos' */
  /*   delay(15);                       // waits 15 ms for the servo to reach the position */
  /* } */
  /* for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees */
  /*   myservo.write(pos);              // tell servo to go to position in variable 'pos' */
  /*   delay(15);                       // waits 15 ms for the servo to reach the position */
                                        // get incoming byte:
  /* } */
  if (Serial.available() > 0) {

    inByte = Serial.read();
    //for debug
    Serial.print("pos heard ");
    Serial.println(inByte);
    /* if(inByte = */
    getReading(inByte);
    /* Serial.println("hello"); */
    /* Serial.println(inByte); */
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');  // send a capital A

    delay(300);
  }
}

void getReading(int pos){
  /* readingData = {0, 0, 0, 0, 0, 0, 0, 0}; //reset the array of value */
  resetReadingData();

  myservo.write(pos);

  for(int i = 0; i < 2; i++){
    for(int r = 0; r < 50; r++) //50 readings, could change depending on amung of light coming in
    readingData[i] += analogRead(analogPins[i]);
  }

  Serial.print(pos);
  Serial.print(" : ");
  for(int i = 0; i < 8; i++){
    Serial.print(readingData[i]);
    if(i != 7){
      Serial.print(", ");
    }
  }
  Serial.println(" : END");
}


void resetReadingData(){
  for(int i = 0; i < 8; i++){
    readingData[i] = 0;
  }
}
