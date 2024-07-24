void setup() {
  // nothing to do here/private/var/folders/8z/spx72zl91fncyx301nggwwyr0000gn/T/.arduinoIDE-unsaved2024622-4832-1hc8yuf.2f3t/Fading/Fading.ino
}
 
void loop() {
  // get a sensor reading:
  int sensorReading = analogRead(A0);
  // map the results from the sensor reading's range
  // to the desired pitch range:
  float frequency = map(sensorReading, 0, 1000, 0, 2000);
  // change the pitch, play for 10 ms:
  tone(8, frequency, 10);
  delay(10);
}