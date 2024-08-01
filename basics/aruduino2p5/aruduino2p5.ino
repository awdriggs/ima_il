void setup() {
  Serial.begin(9600); // Enable the Serial Monitor at 9600 baud
  pinMode(2, INPUT);  // Button is connected to pin 2
}

void loop() {
  int pot1 = analogRead(A0);   // read the 1st potentiometer
  int pot2 = analogRead(A1);   // read the 2nd potentiometer
  int button = digitalRead(2); // read the button

  if (Serial.available() > 0 ) {
    byte incoming = Serial.read(); // read incoming bytes 
		// int incoming = Serial.read();  works as int also
    Serial.print(pot1);
    Serial.print(",");
    Serial.print(pot2);
    Serial.print(",");
    Serial.println(button);
  }
}