// master ArduinoUNO
#include <SoftwareSerial.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define RX_ 10
#define TX_ 11

#define DHT_PIN 4
#define DHT_TYPE DHT11

const int LIMIT                =   10;
unsigned long prev_millis      =    0;
unsigned long current_millis   =    0;
const int time_interval        = 2000;

float t = 0.0;
float h = 0.0;
int state_button = 0;

const int BUTTON = 3;
const int sensorPin = A0;

SoftwareSerial mySerial(RX_, TX_);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  while(!Serial && !mySerial); // Solo es para esperar
                              // que se incialicen UART y UART virtual
  pinMode(BUTTON, INPUT);
  
  Serial.println("Arduino UNO - MAESTRO");
  randomSeed(analogRead(0)); // numeros aleatorios
  for (int i = 0; i < LIMIT; i++) {
    Serial.println(); // Solo para dejar espacio en blanco
  }
}

void loop() {
  // Simular temperatura
  // float temp = 25.0 + (random(-50, 51) / 10.0);
  
  unsigned long current_millis = millis();
  if (current_millis - prev_millis >= time_interval) {
    prev_millis = current_millis;

    // Leer temperatura
    int value = analogRead(sensorPin);
    float milli_volts = (value / 1023.0) * 5000;
    float celsius = milli_volts / 10;
    Serial.println(celsius);
    
      

    // Datos enviados en formato JSON al ESP32 via UART virtual
    // mySerial.print("{\"t\":");
    // mySerial.print(t);
    // mySerial.print(",\"h\":");
    // mySerial.print(h);
    // mySerial.print(",\"btn\":");
    // mySerial.print(state_button);
    // mySerial.println("}");
    
  }

  if (digitalRead(BUTTON)) {
    state_button = HIGH;
    Serial.println("BUTTON ON");
  }
  else {
    state_button = LOW;
    // Serial.println("BUTTON OFF");
  }

}
