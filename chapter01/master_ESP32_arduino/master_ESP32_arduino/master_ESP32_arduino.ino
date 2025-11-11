void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp = 25.0 + (random(-50, 50) / 10.0); // simula temperatura
  Serial.print("T");
  Serial.print(temp);
  Serial.println(" C");
  delay(2000);
}
