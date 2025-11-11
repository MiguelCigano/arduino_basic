#include <SoftwareSerial.h>

SoftwareSerial miSerial(10, 11); // RX TX

void setup() {
  Serial.begin(9600);
  miSerial.begin(4800);
}

void loop() {
  if (miSerial.available()) {
    Serial.write(miSerial.read());
  }
}

