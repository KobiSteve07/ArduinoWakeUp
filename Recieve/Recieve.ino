void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop() {
  if(Serial.available()) {
    String data = Serial.readString();
    if(data.indexOf("retrieve") != -1) {
      Serial.println(data);
      if(data.endsWith("burnerpc1")){
        Serial.print(analogRead(A0));
      }else if(data.endsWith("burnerpc2")) {

      }else if(data.endsWith("burnerpc3")) {

      }else if(data.endsWith("gamingpc")) {
        
      }
    }else if (data.indexOf("toggle") != -1) {
      if(data.endsWith("burnerpc1")){
      
      }else if(data.endsWith("burnerpc2")) {

      }else if(data.endsWith("burnerpc3")) {

      }else if(data.endsWith("gamingpc")) {
      
      }
    }
  }
}