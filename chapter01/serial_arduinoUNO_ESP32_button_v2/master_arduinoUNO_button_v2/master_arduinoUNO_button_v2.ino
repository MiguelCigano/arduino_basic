// master ArduinoUNO
// Puerto Serial 1 -> UART 1 (Monitor Serial) : Serial
// Puerto Serial 2 -> UART 2 (virtual)        : mySerial

#include <SoftwareSerial.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define RX_ 10
#define TX_ 11

#define DHT_PIN 4
#define DHT_TYPE DHT11

// time variables
unsigned long prev_millis      =    0;
unsigned long current_millis   =    0;
const int time_interval        = 2000;

const int LED_RED      = 6;
const int LED_BLUE     = 7;
const int LIMIT        = 10;
const int COUNT_LIMIT  = 15;

volatile bool state    = LOW;
bool last_state        = state;

volatile int count     = 0;
int prev_count         = 0;

float t = 0.0;
float h = 0.0;

SoftwareSerial mySerial(RX_, TX_);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // Configura UART 1 y UART virtual
  Serial.begin(9600);
  mySerial.begin(9600);
  // Agregar un delay

  // Configura entradas (Sensor DHT, Interrupción, )
  dht.begin();
  
  attachInterrupt(digitalPinToInterrupt(2), foo, RISING);
  attachInterrupt(digitalPinToInterrupt(3), stop_, RISING);
  
  // Configura salidas controladas por web
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  Serial.println("Arduino UNO - MAESTRO");

  for (int i = 0; i < LIMIT; i++) {
    Serial.println(); // Solo para dejar espacio en blanco
  }
}

void loop() {

  // Para evitar el uso de delay, 200 ms
  unsigned long current_millis = millis();
  if (current_millis - prev_millis >= time_interval) {
    prev_millis = current_millis;
    
    // Leer temperatura y humedad
    t = dht.readTemperature();
    h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {

      // Datos enviados (impresos) en UART 1
      Serial.print("TEMP:");
      Serial.print(t);
      Serial.print(", HUM:");
      Serial.println(h);

      // Datos enviados en formato JSON al ESP32 via UART virtual
      mySerial.print("{\"t\":");
      mySerial.print(t);
      mySerial.print(",\"h\":");
      mySerial.print(h);
      mySerial.print(",\"btn\":");
      mySerial.print(count);
      mySerial.print(",\"btn2\":");
      mySerial.print(state);
      mySerial.println("}");
    }
  }

  if (prev_count != count) {
    
    Serial.print("Count: ");
    Serial.println(count);
    
    mySerial.print("{\"t\":");
    mySerial.print(t);
    mySerial.print(",\"h\":");
    mySerial.print(h);
    mySerial.print(",\"btn\":");
    mySerial.print(count);
    mySerial.print(",\"btn2\":");
    mySerial.print(state);
    mySerial.println("}");

    if (count >= COUNT_LIMIT) {
      count = 0;
    }

    prev_count = count;

  }

  if (last_state != state) {
    Serial.println("Interrup pin 3!");
    if (state == HIGH) {
      Serial.println("Stop!");

      mySerial.print("{\"t\":");
      mySerial.print(t);
      mySerial.print(",\"h\":");
      mySerial.print(h);
      mySerial.print(",\"btn\":");
      mySerial.print(count);
      mySerial.print(",\"btn2\":");
      mySerial.print(state);
      mySerial.println("}");
    }
    else {
      Serial.println("Run!");

      mySerial.print("{\"t\":");
      mySerial.print(t);
      mySerial.print(",\"h\":");
      mySerial.print(h);
      mySerial.print(",\"btn\":");
      mySerial.print(count);
      mySerial.print(",\"btn2\":");
      mySerial.print(state);
      mySerial.println("}");
    }

    last_state = state;
  }

  // Lectura del puerto mySerial, para recibir mensajes del ESP32
  if (mySerial.available()) {
    String json_str = mySerial.readStringUntil('\n');

    // Verifica que el parseo se haya hecho correctamente y maneja el error
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, json_str);

    if (error) {
      Serial.print("Error de parseo: ");
      Serial.println(error.f_str());
      return;
    }

    // Lee el campo "cmd"
    const char* cmd = doc["cmd"];

    if (cmd && strcmp(cmd, "BOTON_WEB_1") == 0 ) {
      Serial.println("Boton web 1 presionado!");
      digitalWrite(LED_RED, !digitalRead(LED_RED));

      // Puedes mandar una respuesta si quieres, debes adaptar el handleDatos
      // mySerial.println("{\"status\":\"OK\"}");
    }
    else if (cmd && strcmp(cmd, "BOTON_WEB_2") == 0 ) {
      Serial.println("Boton web 2 presionado!");
      digitalWrite(LED_BLUE, !digitalRead(LED_BLUE));
    }
  }

}

void foo() {
  count = count + 1;
}

void stop_() {
  state = !last_state;
}
