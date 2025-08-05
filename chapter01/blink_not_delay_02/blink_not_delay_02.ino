
// set LED
// const int ledPin   = LED_BUILTIN;
// const int ledPin      = 2; // esp32 embedded LED
const int ledPin      = 26; 
int ledState          = LOW;

// time variables
unsigned long prevMillis        = 0;
unsigned long prevMillisOffOn   = 0;
const int intervalOff           = 1000;
const int intervalOffOn         = 4000;  // time of intervalOff + time on

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.print("Init completed\n");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= intervalOff) {
    prevMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
      Serial.print("LED 22 ON!\n");
    }
  }
  else if (currentMillis - prevMillisOffOn >= intervalOffOn) {
    prevMillisOffOn = currentMillis;
    if (ledState == HIGH) {
      ledState = LOW;
      Serial.print("LEd 22 OFF!\n");
    }
  }
  digitalWrite(ledPin, ledState);
}
