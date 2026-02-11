constexpr int LED_RED = 3; 
constexpr int BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_RED, OUTPUT);
}

String input = "";

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {              // fin de mensaje
      int val = input.toInt();  // convertir a num
      val = constrain(val, 0, 255);

      analogWrite(LED_RED, val);

      Serial.print("PWM is ");
      Serial.println(val);

      input = "";                 // limpiar buffer
    } 
    else {
      input += c;                 // acumular caracteres
    }
  }
}