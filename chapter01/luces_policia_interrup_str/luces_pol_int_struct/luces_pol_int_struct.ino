constexpr int LED_RED = 6;
constexpr int LED_BLUE = 5;

volatile bool alert = false;

struct LightPoliceInit {
  int red_light;
  int blue_light; 
  unsigned long previous_time;
  int current_state;
};

LightPoliceInit lightPolice = {LED_RED, LED_BLUE, 0, 0};

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), foo_interruption, RISING);
  pinMode(lightPolice.blue_light, OUTPUT);
  pinMode(lightPolice.red_light, OUTPUT);
}

void light_police_update(LightPoliceInit *lp, 
                        unsigned long normal_interval, 
                        unsigned long alarm_interval) 
{
  unsigned long current_time = millis();
  switch (lp->current_state) 
  {
    /*-------------------RED--------------------*/
    case 0:
      digitalWrite(lp->red_light, HIGH);
      digitalWrite(lp->blue_light, LOW);
      if ((current_time - lp->previous_time) >= normal_interval) 
      {
        lp->previous_time = current_time;
        lp->current_state = 1;
      }
      break;
    /*------------------BLUE-------------------*/
    case 1:
      digitalWrite(lp->red_light, LOW);
      digitalWrite(lp->blue_light, HIGH);
      if ((current_time - lp->previous_time) >= normal_interval) 
      {
        lp->previous_time = current_time;
        lp->current_state = 2;
      }
      break;
    /*-------------------------------------------*/
    default:
      digitalWrite(lp->red_light, LOW);
      digitalWrite(lp->blue_light, LOW);
      if ((current_time - lp->previous_time) >= alarm_interval) 
      {
        lp->previous_time = current_time;
        lp->current_state = 0;
      }
      break;
  }
}

void loop() {
  if (alert) // Se ejecutan luces MODO ALARMA 
  {
    light_police_update(&lightPolice, 300, 50);
  }
  else // Se ejecuta luces MODO NORMAL 
  {
    light_police_update(&lightPolice, 3000, 2000);
  }
}

void foo_interruption() {
  if (alert) {
    alert = false;
  }
  else {
    alert = true;
  }
}
