unsigned long normal_interval = 1000;
unsigned long alarm_interval = 200;
unsigned long previous_time = 0;

bool alert = false;
bool state_red = 0;
bool state_blue = 0;

constexpr int LED_RED = 6;
constexpr int LED_BLUE = 5;

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), foo_interruption, RISING);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void fn_leds() {
  digitalWrite(LED_RED, state_red);
  digitalWrite(LED_BLUE, state_blue);
}

void loop() {
  unsigned long current_time = millis();

  if (alert) // Se ejecutan luces MODO ALARMA 
  {
    if ((current_time - previous_time) >= alarm_interval) 
    {
      previous_time = current_time;
      if (state_red == LOW)
      {
        state_red = HIGH;
        state_blue = LOW;
      }
      else 
      {
        state_red = LOW;
        state_blue = HIGH;
      }
    }
  }
  else // Se ejecuta luces MODO NORMAL 
  {
    if ((current_time - previous_time) >= normal_interval) 
    {
      previous_time = current_time;
      if (state_red == LOW) 
      {
        state_red = HIGH;
        state_blue = LOW;
      }
      else 
      {
        state_red = LOW;
        state_blue = HIGH;
      }
    }
  }
  fn_leds();
}

void foo_interruption() {
  if (alert) {
    alert = false;
  }
  else {
    alert = true;
  }
}
