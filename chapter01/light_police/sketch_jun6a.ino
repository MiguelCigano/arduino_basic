constexpr int LED_RED = 6;
constexpr int LED_BLUE = 5;

constexpr int alarm_interval = 1000; 

struct LightPoliceInit {
  int red_light;        // LED_ROJO
  int blue_light;       // LED_AZUL
  unsigned long previous_time;
  int current_state;
};

LightPoliceInit lightPolice = {LED_RED, LED_BLUE, 0, 0};   // Inicialización

void setup() {
  pinMode(lightPolice.blue_light, OUTPUT);
  pinMode(lightPolice.red_light, OUTPUT);
}

void light_police_update(LightPoliceInit *lp) {
  unsigned long current_time = millis();
  switch (lp->current_state) 
  {
    /*-------------------RED--------------------*/
    case 0:
      digitalWrite(lp->red_light, HIGH);
      digitalWrite(lp->blue_light, LOW);
      if ((current_time - lp->previous_time) >= alarm_interval) 
      {
        lp->previous_time = current_time;
        lp->current_state = 1;
      }
      break;
    /*------------------BLUE-------------------*/
    case 1:
      digitalWrite(lp->red_light, LOW);
      digitalWrite(lp->blue_light, HIGH);
      if ((current_time - lp->previous_time) >= alarm_interval) 
      {
        lp->previous_time = current_time;
        lp->current_state = 2;
      }
      break;
    /*-------------------------------------------*/
    default:
      digitalWrite(lp->red_light, LOW);
      digitalWrite(lp->blue_light, LOW);
      if ((current_time - lp->previous_time) >= 500) 
      {
        lp->previous_time = current_time;
        lp->current_state = 0;
      }
      break;
  }
}

void loop() {
  light_police_update(&lightPolice);
}