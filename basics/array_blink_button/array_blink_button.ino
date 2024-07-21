/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
int myPins[] = { 3, 4, 5 };
int i = 0;
int pushButton = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i <= 2; i++) {
    pinMode(myPins[i], OUTPUT);
  }

  pinMode(pushButton, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState) {
    digitalWrite(myPins[i], LOW);
    i++;

    if (i > 2) {
      i = 0;
    }
    delay(500);
  }
  digitalWrite(myPins[i], HIGH);
  // delay(200);                    // wait for a second
  // digitalWrite(myPins[i], LOW);  // turn the LED off by making the voltage LOW
  
}
