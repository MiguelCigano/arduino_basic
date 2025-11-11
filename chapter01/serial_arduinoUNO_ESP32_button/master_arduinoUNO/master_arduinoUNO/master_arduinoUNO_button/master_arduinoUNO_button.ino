// master ArduinoUNO
#include <SoftwareSerial.h>
#include <DHT.h>

#define RX_ 10
#define TX_ 11

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define BUTTON 3

SoftwareSerial mySerial(RX_, TX_); // RX, TX
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  pinMode(BUTTON, INPUT);
  
  Serial.println("Arduino UNO - MAESTRO");
}

void loop() {
  // Leer temperatura y humedad
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t) && !isnan(h)) {
    Serial.print("TEMP:");
    Serial.print(t);
    Serial.print(", HUM:");
    Serial.println(h);

    // datos enviados como Json
    mySerial.print("{\"t\":");
    mySerial.print(t);
    mySerial.print(",\"h\":");
    mySerial.print(h);
    mySerial.println("}");
  }

  static bool last_state = HIGH;
  bool state = digitalRead(BUTTON);
  if (state != last_state) {
    if (state == LOW) {
      Serial.println("Button free!");
    }
    else {
      mySerial.print("{\"t\":");
      mySerial.print(t);
      mySerial.print(",\"h\":");
      mySerial.print(h);
      mySerial.print(",\"btn\":");
      mySerial.print(state);
      mySerial.println("}");
      Serial.println(state);
    }
    last_state = state;
  }

  delay(2000); // Esperar 2 segundos entre envíos
}
