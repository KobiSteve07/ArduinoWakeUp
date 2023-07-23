int dataToSend = 1; // You can replace this with any data you want to send

void setup() {
  Serial.begin(1200); // Set the baud rate to 1200 (make sure receiver uses the same rate)
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from the receiver Arduino, if available (discard it here)
    int dataToSend = Serial.parseInt();
  }

  // Send data to the receiver Arduino
  Serial.println(dataToSend);
  delay(1000); // Wait for 1 second before sending the next data
}