void setup() {
  Serial.begin(9600);       // initialize serial communications
}
 
void loop() {
  int analogValue = analogRead(A0); // read the analog input
  Serial.println(analogValue);      // print it
 //int val=analogRead(A0); // read the sensor
 
//Serial.println(exp(8.5841-log(analogValue)));
  delay(50); 
}