const int LED_RED    = 3;
const int LED_GREEN  = 5;
const int LED_BLUE   = 6;

int count = 0;
unsigned long last_msg_time = 0;

void setup() {
  Serial.begin(9600);
  // Un timeout pequeño ayuda a que no se congele el loop
  Serial.setTimeout(10); 
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  // Solo procesamos si hay datos y el primer caracter es un número
  // (Esto evita que basura en el puerto apague los LEDs)
  if (Serial.available() > 0) {
    // Leemos hasta encontrar el salto de línea que envía Rust con format!
    String data = Serial.readStringUntil('\n');
    
    // Si la cadena no esta vacia, extraemos los valores
    if (data.length() > 0) {
      // This line is to send data to backend.
      // Serial.println(data);

      int first_comma  = data.indexOf(',');
      int second_comma = data.indexOf(',', first_comma + 1);

      if (first_comma != -1 && second_comma != -1) {
        int r = data.substring(0, first_comma).toInt();
        int g = data.substring(first_comma + 1, second_comma).toInt();
        int b = data.substring(second_comma + 1).toInt();

        analogWrite(LED_RED,   constrain(r, 0, 255));
        analogWrite(LED_GREEN, constrain(g, 0, 255));
        analogWrite(LED_BLUE,  constrain(b, 0, 255));
      
      }
    }
  }

  // Mandar el numero que aumenta (Petición GET)
  if (millis() - last_msg_time > 1000) {
    Serial.println(count); // Esto lo leerá el hilo de lectura de Rust
    count++;
    last_msg_time = millis();
  }
}
