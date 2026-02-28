int sensor_pin = A2;
float voltaje;
float tempC;
int valor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valor = analogRead(sensor_pin);
  // Serial.print("Analog: ");
  // Serial.println(valor);
  // voltaje = valor * (5.0 / 1023.0);
  tempC = ((valor * 5000.0) / 1023) / 10;
  // Serial.print("Temp: ");
  // Serial.println(tempC, 1);
  Serial.print(valor);
  Serial.print(",");
  Serial.println(tempC);
  delay(1000);
}
