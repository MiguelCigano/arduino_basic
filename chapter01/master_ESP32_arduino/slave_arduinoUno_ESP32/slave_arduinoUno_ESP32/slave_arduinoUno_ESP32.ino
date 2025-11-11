// slave arduino uno
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); // RX=10, TX=11

void setup() {
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);     // Para ver en la PC
  mySerial.begin(9600);   // Comunicación con el ESP32
  Serial.println("\nEsperando datos del ESP32...");
}

void loop() {
  mySerial.listen();
  if (mySerial.available()) {
    char t = mySerial.read();
    Serial.write(t); // Muestra lo que llega
  }
  else {
    Serial.println("Fail!");
    delay(4000);
  }
}