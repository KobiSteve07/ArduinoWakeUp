void setup() {
  Serial.begin(1200);
}

void loop() {
  if (Serial.available() > 0) {
    int receivedData = Serial.parseInt();
    Serial.println(1+receivedData);
  }
}