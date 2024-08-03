/*
  read color value from apds9960 breakout
*/

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(115200);

  if (!apds.begin()) {
    Serial.println("failed to initialize device! Please check your wiring.");
  } else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void loop() {
  //create some variables to store the color data in
  uint16_t r, g, b, c;
  float red, green, blue;

  //wait for color data to be ready
  while (!apds.colorDataReady()) {
    delay(5);
  }

  //get the raw data and print the different channels
  apds.getColorData(&r, &g, &b, &c);
  //Serial.print("red: ");
  //Serial.print(r);
  //Serial.print(" green: ");
  //Serial.print(" blue: ");
  //Serial.print(b);
  //Serial.print(" clear: ");
  //Serial.println(c);
  //Serial.println();

  //calculate rgb
  //individual values are a % of the ambient(c) light
  //so dividing any channel by the ambient light gives you a value from 0 to 1
  //multiplying by 255 moves it into rgb value mode.
  red = (255 * r / c);
  green = (255 * g / c);
  blue = (255 * b / c);

  //for communicating with p5, send the color value when asked.
  if (Serial.available() > 0) {
    byte incoming = Serial.read();  // read incoming bytes
                                    // int incoming = Serial.read();  works as int also
    Serial.print(red);
    Serial.print(",");
    Serial.print(green);
    Serial.print(",");
    Serial.print(blue);
    Serial.println("");
  }


  delay(500);
}