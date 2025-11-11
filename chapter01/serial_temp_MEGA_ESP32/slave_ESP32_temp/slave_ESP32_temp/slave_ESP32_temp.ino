// ESP32: recibe datos del Mega y los reenvía al PC

#define RX_ 16  // pin RX del ESP32 conectado al TX del Mega
#define TX_ 17  // pin TX del ESP32 conectado al RX del Mega (no se usa aquí)

// Configuración de UART
void setup() {
  Serial.begin(115200); // USB al PC
  Serial2.begin(9600, SERIAL_8N1, RX_, TX_); // UART con Mega
}

void loop() {
  // Leer datos que vienen del Mega
  while (Serial2.available()) {
    // Leer línea completa desde Mega
    String line = Serial2.readStringUntil('\n'); 
    line.trim(); // elimina espacios o retornos de carro
    if (line.length() > 0) {
      Serial.println(line); // envía al PC con '\n' para la web
    }
  }
}
