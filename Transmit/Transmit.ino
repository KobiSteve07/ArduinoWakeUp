void setup() {
  delay(10000);
  Serial.begin(1200); // Set the baud rate to 9600 (make sure receiver uses the same rate)
  Serial.println(1);
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from the receiver Arduino, if available (discard it here)
    int receivedData = Serial.parseInt();
    Serial.println(1+receivedData);
  }
}
