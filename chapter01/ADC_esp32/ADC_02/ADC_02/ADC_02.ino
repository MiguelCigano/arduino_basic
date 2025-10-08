float sensor_pin = 32;
float tempC;
float valor;

void setup() {
  Serial.begin(115200); // ESP32 suele usar 115200
  delay(500);
}

void loop() {
  valor = (float)analogRead(sensor_pin); 
  // Convertir ADC a temperatura en °C
  // ADC ESP32 por defecto 12 bits (0–4095)
  float voltaje = valor * (3.3 / 4095.0); // 3.3V de referencia
  tempC = voltaje * 100.0; // LM35: 10mV/°C

  Serial.println(tempC);

  delay(1000);
}