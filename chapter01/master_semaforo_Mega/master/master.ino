#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del módulo (normalmente 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);
int pot;
constexpr int pin_pot = A0; 

void setup() {
  lcd.init();             // Inicializar LCD
  lcd.backlight();        // Encender retroiluminación
  lcd.setCursor(0, 0);
  lcd.print("SEMAFORO CUT");

  pinMode(2, OUTPUT); // rojo
  pinMode(3, OUTPUT); // amarillo
  pinMode(4, OUTPUT); // verde

  Serial.begin(9600);   // Para monitor serial del IDE
  Serial1.begin(9600); // Comunicación con ESP32
}

void loop() {
  
  digitalWrite(2, HIGH); digitalWrite(3, LOW); digitalWrite(4, LOW);
  Serial.println("ROJO");
  Serial1.println("ROJO");
  lcd.setCursor(0, 1);
  lcd.print("ROJO    ");
  delay(1000);

  digitalWrite(2, LOW); digitalWrite(3, HIGH); digitalWrite(4, LOW);
  Serial.println("AMARILLO");
  Serial1.println("AMARILLO");
  lcd.setCursor(0, 1);
  lcd.print("AMARILLO");
  delay(1000);
  // lcd.setCursor(0, 1);
  // lcd.clear();

  digitalWrite(2, LOW); digitalWrite(3, LOW); digitalWrite(4, HIGH);
  Serial.println("VERDE");
  Serial1.println("VERDE");
  lcd.setCursor(0, 1);
  lcd.print("VERDE   ");
  delay(1000);
  
  pot = analogRead(A7);
  // float temp_C = ( pot * 5 * 100 ) / 1023.0;
  // pot = map(temp_C, 20, 50, 21, 83);
  lcd.setCursor(8, 1);
  lcd.print("| T: ");
  lcd.print(pot, 1);
}
