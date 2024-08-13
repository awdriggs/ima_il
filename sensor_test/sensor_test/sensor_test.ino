int analogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++) {
    pinMode(analogPins[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 2; i++) {
        int sensorValue = analogRead(analogPins[i]);
        Serial.print(i);
        Serial.print(" ");
        Serial.println(sensorValue);
  }
  delay(500);
}
