// master ArduinoUNO
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("Arduino UNO - MAESTRO");
  randomSeed(analogRead(0)); // numeros aleatorios
}

void loop() {
  // Simular temperatura
  float temp = 25.0 + (random(-50, 51) / 10.0);

  // Enviar datos al ESP32
  // mySerial.print("T");
  mySerial.println(temp);
  // mySerial.println(" C");
  
  // Mostrar en monitor serial local
  Serial.print("Enviado: ");
  Serial.print(temp);
  Serial.println(" °C");
  
  delay(2000); // Esperar 2 segundos entre envíos
}
