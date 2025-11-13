#include <ArduinoJson.h>

#define RX_ 16
#define TX_ 17

const int LIMIT = 10;
float temperatura = 0.0;
float humedad = 0.0;
int state_button = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX_, TX_);
  while(!Serial && !Serial2); // Solo es para esperar
                              // que se incialicen los UART
  Serial.println("ESP32 - ESCLAVO");

  for (int i = 0; i < LIMIT; i++) {
    Serial.println(); // Solo para dejar espacio en blanco
  }
}

void loop() {
  // Leer UART 2 y enviar a PC usando UART 1
  if (Serial2.available()) {
    String json_str = Serial2.readStringUntil('\n');
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, json_str);
    
    if (!error) {
      temperatura = doc["t"];
      humedad = doc["h"];
      state_button = doc["btn"];

      Serial.println(temperatura);
      // Serial.println(humedad);

      if (state_button == 1) {
        // Serial.println("LED ON");
      }
      else {
        // Serial.println("LED OFF");
      }
    }
    else {
      Serial.println("[Fail] - leer Json");
    }
  }

}