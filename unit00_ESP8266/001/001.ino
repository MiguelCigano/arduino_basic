#include <ESP8266WiFi.h>

// credenciales
const char *ssid = "IZZI-BA68";
const char *password = "50A5DC2CBA68";

void setup() {
    Serial.begin(115200);
    delay(1000); // Pequeña pausa para que se inicialice bien
    Serial.println("\nIniciando...");

    // WiFi.mode(WIFI_STA); // Asegura que estamos en modo Estación (STA)
    WiFi.begin(ssid, password);

    Serial.print("Conectando a WiFi");
    int intentos = 0;

    while (WiFi.status() != WL_CONNECTED && intentos < 20) { // Espera hasta 10 segundos
        delay(500);
        Serial.print("fail");
        intentos++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n¡Conectado a WiFi!");
        Serial.print("IP asignada: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n⚠️ No se pudo conectar a WiFi");
    }
}

void loop() {
    // Nada aquí por ahora
}