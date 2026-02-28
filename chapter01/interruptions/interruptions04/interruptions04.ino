#include<stdint.h>

// imcomplete!

constexpr int LED_1 = 3;
constexpr int LED_2 = 4;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (prev_count != count) {
    if (count < 10) {
      // Alternar LED_1
      if (count % 2 == 0) {
        // Valor de count es PAR
        digitalWrite(LED_1, LOW);
      }
      else {
        // Valor de count is IMPAR
        digitalWrite(LED_1, HIGH);
      }
    }
    else if (count >= 10) {
      // Encender LED_2
      Serial.print("LED_2");
      digitalWrite(LED_2, HIGH);
    }
    else {
      Serial.print("No se ejecuto nada");
    }
  }
  
}
