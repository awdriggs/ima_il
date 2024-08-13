// Define an array to hold the analog pins A0 to A7
#include <Servo.h>

Servo myservo;  // create Servo object to control a servo

int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };
//int pixelArray[180][8];
int pos = 0;
int pass = 0;
int totalPasses = 5;

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object

  // Optionally, you can set the pins as input, though it's not necessary for analogRead
  for (int i = 0; i < 8; i++) {
    pinMode(analogPins[i], INPUT);
  }
}

void loop() {
  // Read and print the values from the analog pins
  if (pass < totalPasses) {
    Serial.println(pass);


    //number of passes?
    //one pass
    //for each servo position
    for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(15);           // waits 15 ms for the servo to reach the position
      //how many readings to take at each position?
      for (int i = 0; i < 5; i++) {
        takeReading(pos);
      }
    }
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      delay(15);                           // waits 15 ms for the servo to reach the position
      //take readings
      for (int i = 0; i < 5; i++) {
        takeReading(pos);
      }
    }

    delay(15);
    //push out a serial event to p5 for rendering
    pass++;
  }
  Serial.println("done");
}

void takeReading(int pos) {
  Serial.print(pos);
  Serial.print(":");
  
  //use json?
  
  // //for each "pixel", e.g. a photoresistor
  
  for (int i = 0; i < 8; i++) {
    
  //   //store the old average
  //   int current = pixelArray[pos][i];  //get the current value;
    int sensorValue = analogRead(analogPins[i]);
    Serial.print(sensorValue);
    if(i < 7){
      Serial.print(" ");
    }
    
  //   //get the new value
    

  //   //average the old value with the new value
  //   int avg = (current + sensorValue) / 2;

  //   pixelArray[pos][i] = avg;  //assign the new value
    
  }
  Serial.println();
}

