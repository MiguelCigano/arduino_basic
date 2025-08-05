// definicion de variables constantes conocidas en tiempo de compilacion
constexpr int buttonPin     = 8;
constexpr int toggleLedPin  = 7;
constexpr int blinkLedPin   = 6;

// estado inicial para el blink LED
int blinkLedState = LOW;

// estado inicial para el toggle LED 
int toggleLedState      = LOW;

// variables para el push button
bool initStateButton    = LOW;
bool currentStateButton = LOW;
int readingStateButton;

// variables para task 1 (blink)
unsigned long previousTime             = 0;
constexpr unsigned long intervalTime01 = 1000;

// variables para task 2 (toggle)
unsigned long pushButtonTime           = 0;
constexpr unsigned long intervalTime02 = 500;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  // Serial.print("");
  pinMode(buttonPin, INPUT);
  pinMode(toggleLedPin, OUTPUT);
  pinMode(blinkLedPin, OUTPUT);

  digitalWrite(toggleLedPin, toggleLedState);
  digitalWrite(blinkLedPin, blinkLedState);
}

void loop() {
  unsigned long currentTime = millis();

  // task 1 (blink)
  if (currentTime - previousTime >= intervalTime01) {
    previousTime = currentTime;
    if (blinkLedState == LOW) {
      blinkLedState = HIGH;
    }
    else {
      blinkLedState = LOW;
    }
    digitalWrite(blinkLedPin, blinkLedState);
  }

  // task 2 (toggle)
  readingStateButton = digitalRead(buttonPin);
  if (readingStateButton != initStateButton) {
    pushButtonTime = currentTime;
    initStateButton = readingStateButton;
    // Serial.print("Push Button press init\n");
  }

  if ((currentTime - pushButtonTime) >= intervalTime02) {
    // Serial.print("Complete time to avoid debounce\n");
    if (readingStateButton != currentStateButton) {
      currentStateButton = readingStateButton;
      
      if (currentStateButton == LOW) {
        toggleLedState = LOW;
        Serial.print("LED OFF\n");
      }
      else {
        toggleLedState = HIGH;
        Serial.print("LED ON\n");
      }
      digitalWrite(toggleLedPin, toggleLedState);
    }
  }
}



// // --- Apagado inmediato al soltar ---
// if (buttonReading == LOW && lastStableButtonState == HIGH) {
//   lastStableButtonState = LOW;
//   toggleLedState = LOW;
//   Serial.println("LED OFF");
//   digitalWrite(toggleLedPin, toggleLedState);
// }
