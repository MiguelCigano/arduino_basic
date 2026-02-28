volatile int count = 0;
int prev_count = 0;
constexpr int LED_RED = 1;
constexpr int LED_BLUE = 3;
constexpr int LIMIT_MAX = 20;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), foo_interruption, RISING);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  for (int i = 0; i < 20; i++) {
    Serial.println();  // imprime 20 saltos de línea
  }
}

void loop() {
  if (prev_count != count) {
    Serial.print("Contador: ");
    Serial.println(count);
    digitalWrite(LED_RED, !digitalRead(3));
    if (count == LIMIT_MAX) {
      digitalWrite(LED_BLUE, HIGH);
    }
    prev_count = count;
  }
  else {
    // TODO
  }
}

void foo_interruption() {
    count = count + 1;
}