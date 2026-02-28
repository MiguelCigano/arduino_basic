const int directionPin = 3;
const int stepPin      = 2;


void setup() {
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop() {
  digitalWrite(directionPin, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(3000);
  }

  delay(1000);

  digitalWrite(directionPin, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);

}
