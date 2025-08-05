struct LightPoliceInit {
  int redLight;
  int blueLight; 
  unsigned long prevMillis;
  int currentState;
};

LightPoliceInit lightPolice = { 8, 9, 0, 0};

void setup() {
  pinMode(lightPolice.blueLight, OUTPUT);
  pinMode(lightPolice.redLight, OUTPUT);
}

void light_police_update(LightPoliceInit *lp) {
  unsigned long currentMillis = millis();
  switch (lp->currentState) {
    case 0:
      digitalWrite(lp->redLight, HIGH);
      digitalWrite(lp->blueLight, LOW);
      if ((currentMillis - lp->prevMillis) >= 1000) {
        lp->prevMillis = currentMillis;
        lp->currentState = 1;
      }
      break;
    case 1:
      digitalWrite(lp->redLight, LOW);
      digitalWrite(lp->blueLight, HIGH);
      if ((currentMillis - lp->prevMillis) >= 1000) {
        lp->prevMillis = currentMillis;
        lp->currentState = 2;
      }
      break;
    default:
      digitalWrite(lp->redLight, LOW);
      digitalWrite(lp->blueLight, LOW);
      if ((currentMillis - lp->prevMillis) >= 500) {
        lp->prevMillis = currentMillis;
        lp->currentState = 0;
      }
      break;
  }
}

void loop() {
  light_police_update(&lightPolice);
}