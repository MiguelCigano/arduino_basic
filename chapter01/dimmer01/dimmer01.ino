#include<TimerOne.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(52, 50, 11, 10, 9, 8); // (RS, E, D4, D5, D6, D7)

volatile int count_ge = 0;
volatile int pot;
constexpr int pin_shot = 7;
constexpr int pin_pot = A0;

void setup() {
  attachInterrupt(0, zero_cross,RISING);
  Timer1.initialize(48);
  Timer1.attachInterrupt(increment_grade);
  pinMode(pin_shot, OUTPUT);
  digitalWrite(pin_shot, LOW);

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  pot = analogRead(pin_pot);
  pot = map(pot, 0, 1023, 21, 83);

  lcd.setCursor(0,0);
  lcd.print("Trigger:");
  lcd.setCursor(8,0);
  lcd.print(pot);
  lcd.print("     ");
  lcd.setCursor(0,1);
}

// funcion de interrupcion externa por cruce por cero
void zero_cross() {
  count_ge = 0;
}

// funcion de interrupcion interna por timer
void increment_grade() {
  count_ge = count_ge + 1;
  if (pot == count_ge) {
    digitalWrite(pin_shot, HIGH); // 62.5 ns
    // delay(1);
    digitalWrite(pin_shot, LOW);
  }
}
