void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 (ajustar acorde a tu conexión con el Mega)
}

void loop() {

  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}