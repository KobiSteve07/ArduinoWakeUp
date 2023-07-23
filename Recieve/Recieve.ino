void setup() {
  Serial.begin(1200); // Set the baud rate to 1200 (make sure transmitter uses the same rate)
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from the transmitter Arduino, if available
    int receivedData = Serial.parseInt();
    Serial.println(1+receivedData);
  }
}