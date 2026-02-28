#include <WiFi.h>
#include <WebServer.h>

// const char* ssid = "IZZI-BA68";
// const char* password = "";

// const char* ssid = "INFINITUM74C0_5";
// const char* password = "mc02wwwP0M";

const char* ssid = "Galaxy A55 5G B426";
const char* password = "Tako0394";

String estadoSemaforo = "Desconocido";

WebServer server(80);

void handleRoot() {
  String colorRojo = "gray";
  String colorAmarillo = "gray";
  String colorVerde = "gray";

  if (estadoSemaforo == "ROJO") colorRojo = "red";
  else if (estadoSemaforo == "AMARILLO") colorAmarillo = "orange";
  else if (estadoSemaforo == "VERDE") colorVerde = "green";

  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta http-equiv='refresh' content='1'/>
      <title>Semaforo</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          text-align: center;
          background-color: #f0f0f0;
          margin-top: 50px;
        }
        .semaforo {
          width: 100px;
          margin: auto;
          padding: 20px;
          background-color: #333;
          border-radius: 20px;
          box-shadow: 0 0 10px rgba(0,0,0,0.5);
        }
        .luz {
          width: 60px;
          height: 60px;
          margin: 15px auto;
          border-radius: 50%;
          background-color: gray;
          box-shadow: inset 0 0 10px rgba(0,0,0,0.5);
        }
        .rojo { background-color: )rawliteral" + colorRojo + R"rawliteral(; }
        .amarillo { background-color: )rawliteral" + colorAmarillo + R"rawliteral(; }
        .verde { background-color: )rawliteral" + colorVerde + R"rawliteral(; }
      </style>
    </head>
    <body>
      <h1>Semaforo CUT</h1>
      <div class='semaforo'>
        <div class='luz rojo'></div>
        <div class='luz amarillo'></div>
        <div class='luz verde'></div>
      </div>
      <p style="margin-top: 20px; font-size: 20px;">Luz actual: <strong>)rawliteral" + estadoSemaforo + R"rawliteral(</strong></p>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 (ajustar acorde a tu conexión con el Mega)

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  if (Serial2.available()) {
    estadoSemaforo = Serial2.readStringUntil('\n');
    estadoSemaforo.trim();
    Serial.println("Recibido: " + estadoSemaforo);
  }
}


