const int numReadings = 100;

int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average

void setup() {
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
 
void loop() {
  // get a sensor reading:
  int sensorReading = analogRead(A0);

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensorReading;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  Serial.println(sensorReading);      // print it

  // map the results from the sensor reading's range
  // to the desired pitch range:
  float frequency = map(sensorReading, 180, 800, 0, 2000);
  // change the pitch, play for 10 ms:
  tone(8, frequency, 10);
  delay(5);
}


 
