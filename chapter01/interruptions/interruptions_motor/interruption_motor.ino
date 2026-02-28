#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int count = 0;
int prev_count = 0;

constexpr int LED_RED = 1;
constexpr int LED_BLUE = 3;
constexpr int LIMIT_MAX = 20;

constexpr int ENA = A5;
constexpr int IN1 = 5;
constexpr int IN2 = 6;

bool turn_dir = false;
bool init_motor = true;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), foo, RISING);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  for (int i = 0; i < 20; i++) {
    Serial.println();
  }
}

void init_right_motor() {
  for (int velocidad = 0; velocidad < 250; velocidad ++) {
    analogWrite(ENA, velocidad);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(20);
  }
}

void right_motor() {
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void left_motor() {
  analogWrite(ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void pause_motor() {
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Count 2: ");
  lcd.print(count);

  if (init_motor) {
    init_right_motor();
    init_motor = false;
  }

  if (prev_count != count) {
    Serial.print("Count 2: ");
    Serial.println(count);
    digitalWrite(LED_BLUE, !digitalRead(LED_BLUE));
    if (count >= 10) {
      digitalWrite(LED_RED, HIGH);
      pause_motor();
      delay(1000);
      turn_dir = true;
      if (count > 15) {
        count = 0;
        turn_dir = false;
        lcd.clear();   // Borra toda la pantalla
      }
    }
    prev_count = count;
  }

  if (turn_dir == false) {
    right_motor();
  }
  else if (turn_dir == true) {
    left_motor();
  }
}

void foo() {
  count = count + 1;
}
