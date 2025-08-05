#include <LiquidCrystal_I2C.h>
#include  <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);  //

float tempC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(16, 0);
}

void loop() {
  tempC = analogRead(25);
  tempC = (5.0*tempC*100.0)/1024.0;
  Serial.print(tempC);
  Serial.print(" \n");
  // put your main code here, to run repeatedly:
  lcd.scrollDisplayLeft();
  delay(900);
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
}
