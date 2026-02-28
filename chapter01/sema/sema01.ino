#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del módulo (normalmente 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines Semáforo A
constexpr int A_green = 1;
constexpr int A_yellow = 2;
constexpr int A_red = 3;
 
// Pines Semáforo B
constexpr int B_green = 4;
constexpr int B_yellow = 5;
constexpr int B_red = 6;

 
// Tiempo
unsigned long previousMillis = 0;
unsigned long interval = 0;
 
// Estados posibles del sistema
enum TrafficState {
  A_GREEN_B_RED,
  A_YELLOW_B_RED,
  A_RED_B_GREEN,
  A_RED_B_YELLOW
};
 
TrafficState currentState = A_GREEN_B_RED;
 
void setup() {
  Serial.begin(9600);   // Para monitor serial del IDE
  // Serial1.begin(9600); // Comunicación con ESP32
  // Pines como salida
  int allPins[] = {A_green, A_yellow, A_red, B_green, B_yellow, B_red};
  for (int i = 0; i < 6; i++) {
    pinMode(allPins[i], OUTPUT);
  }

  lcd.init();             // Inicializar LCD
  lcd.backlight();        // Encender retroiluminación
  lcd.setCursor(0, 0);
  lcd.print("SEMAFORO CUT");
 
  // Iniciar LCD
  // lcd.begin(16, 2);
  // lcd.setCursor(0, 0);
  // lcd.print(" Cruce Vehicular ");
  // lcd.setCursor(2, 1);
  // lcd.print("Microcontroladores");
  // delay(2000);
  // lcd.clear();
}
 
void updateLightsAndLCD() {
  unsigned long currentMillis = millis();
 
  switch (currentState) {
    case A_GREEN_B_RED:
      interval = 5000;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = A_YELLOW_B_RED;
      }
      digitalWrite(A_green, HIGH);
      digitalWrite(A_yellow, LOW);
      digitalWrite(A_red, LOW);
 
      digitalWrite(B_green, LOW);
      digitalWrite(B_yellow, LOW);
      digitalWrite(B_red, HIGH);

      Serial.println("VERDE");
      lcd.setCursor(0, 0);
      lcd.print(" A: SIGA  B: ALTO ");
      break;
 
    case A_YELLOW_B_RED:
      interval = 1000;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = A_RED_B_GREEN;
      }
      digitalWrite(A_green, LOW);
      digitalWrite(A_yellow, HIGH);
      digitalWrite(A_red, LOW);
 
      digitalWrite(B_green, LOW);
      digitalWrite(B_yellow, LOW);
      digitalWrite(B_red, HIGH);
 
      lcd.setCursor(0, 0);
      lcd.print("A: PRECAU B: ALTO");
      break;
 
    case A_RED_B_GREEN:
      interval = 1000;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = A_RED_B_YELLOW;
      }
      digitalWrite(A_green, LOW);
      digitalWrite(A_yellow, LOW);
      digitalWrite(A_red, HIGH);
 
      digitalWrite(B_green, HIGH);
      digitalWrite(B_yellow, LOW);
      digitalWrite(B_red, LOW);
 
      lcd.setCursor(0, 0);
      lcd.print(" A: ALTO B: SIGA ");
      break;
 
    case A_RED_B_YELLOW:
      interval = 1000;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = A_GREEN_B_RED;
      }
      digitalWrite(A_green, LOW);
      digitalWrite(A_yellow, LOW);
      digitalWrite(A_red, HIGH);
 
      digitalWrite(B_green, LOW);
      digitalWrite(B_yellow, HIGH);
      digitalWrite(B_red, LOW);
 
      lcd.setCursor(0, 0);
      lcd.print(" A: ALTO B: PRECA");
      break;
  }
 
  // Limpiar segunda línea
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
 
void loop() {
  updateLightsAndLCD();
}