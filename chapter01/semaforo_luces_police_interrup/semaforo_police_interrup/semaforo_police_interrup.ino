unsigned long normal_interval = 5000;
unsigned long ambar_interval = 1000;
unsigned long alarm_interval = 100;
unsigned long previous_time = 0;

bool alert = false;
bool state_red = 0;
bool state_blue = 0;
bool state_yellow = 0;

constexpr int LED_RED = 7;
constexpr int LED_BLUE = 6;
constexpr int LED_YELLOW = 5;

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), foo_interruption, RISING);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
}

void fn_leds() {
  digitalWrite(LED_RED, state_red);
  digitalWrite(LED_BLUE, state_blue);
  digitalWrite(LED_YELLOW, state_yellow);
}

void loop() {
  unsigned long current_time = millis();

  if (alert) // Se ejecutan luces POLICIA MODO ALARMA 
  {
    if ((current_time - previous_time) >= alarm_interval) 
    {
      previous_time = current_time;
      if (state_red == LOW)
      {
        state_red = HIGH;
        state_blue = LOW;
        state_yellow = LOW;
      }
      else 
      {
        state_red = LOW;
        state_blue = HIGH;
        state_yellow = LOW;
      }
    }
  }
  else // Se ejecuta luces MODO SEMAFORO 
  {
    if ((current_time - previous_time) >= normal_interval) 
    {
      previous_time = current_time;
      if (state_red == LOW) 
      {
        state_red = HIGH;
        state_blue = LOW;
        state_yellow = LOW;
      }
      else if (state_red == HIGH) 
      {
        state_red = LOW;
        state_blue = LOW;
        state_yellow = HIGH;
      }
    }
    else if ((current_time - previous_time) >= ambar_interval && state_yellow)
    {
      previous_time = current_time;
      if (state_yellow == HIGH)
      {
        state_red = LOW;
        state_blue = HIGH;
        state_yellow = LOW;
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