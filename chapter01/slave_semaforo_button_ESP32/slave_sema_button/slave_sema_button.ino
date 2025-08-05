#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IZZI-BA68";
const char* password = "50A5DC2CBA68";

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
      <title>Semáforo</title>
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
        button {
          margin-top: 30px;
          padding: 10px 20px;
          font-size: 18px;
          border: none;
          background-color: #007bff;
          color: white;
          border-radius: 8px;
          cursor: pointer;
        }
        button:hover {
          background-color: #0056b3;
        }
      </style>
    </head>
    <body>
      <h1>Semáforo CUT</h1>
      <div class='semaforo'>
        <div class='luz rojo'></div>
        <div class='luz amarillo'></div>
        <div class='luz verde'></div>
      </div>
      <p style="margin-top: 20px; font-size: 20px;">Luz actual: <strong>)rawliteral" + estadoSemaforo + R"rawliteral(</strong></p>
      <form action="/encender" method="POST">
        <button type="submit">Encender desde ESP</button>
      </form>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleEncender() {
  Serial2.println("ENCENDER");
  Serial.println("Mensaje enviado al Mega: ENCENDER");
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/encender", HTTP_POST, handleEncender);
  server.begin();
}

void loop() {
  server.handleClient();

  if (Serial2.available()) {
    estadoSemaforo = Serial2.readStringUntil('\n');
    estadoSemaforo.trim();
    Serial.println("Recibido desde Mega: " + estadoSemaforo);
  }
}
