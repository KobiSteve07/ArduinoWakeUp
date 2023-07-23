void setup() {
  Serial.begin(1200); // Set the baud rate to 1200 (make sure transmitter uses the same rate)
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(6000);
  digitalWrite(4, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from the transmitter Arduino, if available
    int receivedData = Serial.parseInt();
    Serial.println(receivedData);

    // Process the received data (if needed)
    // For example, you can send a response back to the transmitter:
    int response = receivedData + 1;
    Serial.println(response);
    Serial.println(); // To add a line break between responses
  }
}