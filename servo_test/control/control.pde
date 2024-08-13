import processing.serial.*;     // import the Processing serial library
Serial myPort;                  // The serial port


void setup() {
  size(640, 480);

  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());

  // I know that the first port in the serial list on my Mac is always my
  // Arduino board, so I open Serial.list()[0].
  // Change the 0 to the appropriate number of the serial port that your
  // microcontroller is attached to.
  myPort = new Serial(this, Serial.list()[2], 9600);

  // read bytes into a buffer until you get a linefeed (ASCII 10):
  myPort.bufferUntil('\n');
}

void draw() {
  background(100);
  // Draw the shape
  for(int i = 0; i < 180; i++){
    myPort.write(i);
    delay(100); //give time to get ther reading back?
  }
   
  for(int i = 180; i > 0; i--){
    myPort.write(i);
    delay(100); //maybe wait for a new reading here instead
  }
}

// serialEvent method is run automatically by the Processing applet whenever
// the buffer reaches the  byte value set in the bufferUntil()
// method in the setup():

void serialEvent(Serial myPort) {
  // read the serial buffer:
  String myString = myPort.readStringUntil('\n');
  println(myString);
  // if you got any bytes other than the linefeed:
  /* myString = trim(myString); */

  /* // split the string at the commas and convert the sections into integers: */
  /* int sensors[] = int(split(myString, ',')); */

  /* // print out the values you got: */
  /* for (int sensorNum = 0; sensorNum < sensors.length; sensorNum++) { */
  /*   print("Sensor " + sensorNum + ": " + sensors[sensorNum] + "\t"); */
  /* } */
  /* // add a linefeed after all the sensor values are printed: */
  /* println(); */
  /* if (sensors.length > 1) { */
  /*   xpos = map(sensors[0], 0, 1023, 0, width); */
  /*   ypos = map(sensors[1], 0, 1023, 0, height); */
  /*   fgcolor = sensors[2]; */
  /* } */
  // send a byte to ask for more data:
  //myPort.write("A");
}
