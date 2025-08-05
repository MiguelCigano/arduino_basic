// just enconder

int pinA = 3;
volatile int contador     = 0;
unsigned long prevMillis  = 0;
const int intervalOff     = 1000;

void setup() {
  pinMode(pinA, INPUT);
  Serial.begin(9600);
  attachInterrupt(1, interrup, RISING); // Flanco de subida pin 3
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= intervalOff) {
    prevMillis = currentMillis;
    Serial.print("p/s: ");
    Serial.println(contador);
    contador = 0;
  }
}

void interrup() {
  contador++;
}