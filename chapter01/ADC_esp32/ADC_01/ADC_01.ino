int sensor_pin = 32; // pin ADC donde está conectado el wiper
float valorADC;

void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
  valorADC = (float)analogRead(sensor_pin); // 0–4095
  Serial.println(valorADC);          // envia valor crudo
  delay(400);                        // actualizar cada 0.1 s
}