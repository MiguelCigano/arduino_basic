// Esclavo ESP32
// Puerto Serial 1 -> UART 1 (Monitor Serial) : Serial
// Puerto Serial 2 -> UART 2                  : Serial2

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define RX_ 16
#define TX_ 17

// Configuración WiFi
const char* ssid = "IZZI-BA68";
const char* password = "50A5DC2CBA68";

WebServer server(80);

float temperatura   = 0.0;
float humedad       = 0.0;
int boton           = 0;
int conteo          = 0;
String state_button = "Sin mensaje";

// Página principal HTML
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Arduino UNO -> ESP32</title>
  <style>
    body {
      background: linear-gradient(145deg, #1a1a1a, #cec3c3ff);
      color: #e0e0e0;
      font-family: Arial; 
      text-align: center; 
      margin: 0; 
      padding: 20px; 
    }
    .container { 
      max-width: 400px; 
      margin: auto; 
      background: white; 
      padding: 25px; 
      border-radius: 15px;
      border: 3px solid #3a3939ff;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1); 
    }
    h1 { 
      color: #0ed8c7ff; 
    }
    .dato { 
      font-size: 30px; 
      margin: 20px 0; 
      padding: 15px; 
      border-radius: 30px; 
    }
    .temp { 
      color: #c0392b; 
      background: #fadbd8; 
    }
    .hum { 
      color: #2980b9; 
      background: #d6eaf8; 
    }
    .conteo { 
      color: #8e44ad; 
      background: #f5eafc;
      border: 3px solid #000000ff;
    }
    .estadoBoton {
      width: 100px; 
      height: 100px; 
      margin: 20px auto;
      border-radius: 50%; 
      display: flex; 
      align-items: center; 
      justify-content: center;
      color: white; 
      font-weight: bold; 
      font-size: 20px;
      transition: background 0.5s ease;
    }
    .activo { 
      background: red; 
      box-shadow: 0 0 15px rgba(255,0,0,0.7); 
    }
    .inactivo { 
      background: green; 
      box-shadow: none; 
    }
    #ultima-actualizacion { 
      color: #7f8c8d; 
      margin-top: 20px; 
    }
    .enviar-boton {
      background: #27ae60;
      color: white;
      cursor: pointer;
      box-shadow: 0 4px 10px rgba(0,0,0,0.2);
      transition: transform 0.1s ease;
    }
    .enviar-boton:active {
      transform: scale(0.9);
      background: #2ecc71;
    }
    #estado-led-rojo {
      transition: color 0.5s ease;
    }
    #estado-led-azul {
      transition: color 0.5s ease;
    }
    
  </style>
</head>
<body>
  <div class="container">
    <h1>🌡️ DHT11 - P1 </h1>

    <div class="dato temp">🔥 Temperatura: <span id="temperatura">0</span>°C</div>
    <div class="dato hum">💧 Humedad: <span id="humedad">0</span>%</div>
    <div class="dato conteo">🔢 Conteo: <span id="conteo">0</span></div>

    <div id="indicador" class="estadoBoton inactivo">
      OFF
    </div>

    <button onclick="enviarComando('BOTON_WEB_1')" style="
      background: #ff1900ff; 
      color: white; 
      border: none; 
      padding: 15px 25px; 
      font-size: 18px; 
      border-radius: 10px;
      cursor: pointer; 
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
    ">
    Enviar al Arduino
    </button>

    <div 
      id="estado-led-rojo"
      style="font-size:18px;
      color:#c0392b;
      padding: 15px 25px;
      font-weight:bold;
    ">
      LED ROJO APAGADO
    </div>

    <button onclick="enviarComando('BOTON_WEB_2')" style="
      background: #002fffff; 
      color: white; 
      border: none; 
      padding: 15px 25px; 
      font-size: 18px; 
      border-radius: 10px;
      cursor: pointer; 
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
    ">
    Enviar al Arduino 2
    </button>

    <div 
      id="estado-led-azul"
      style="font-size:18px;
      color:#c0392b;
      padding: 15px 25px;
      font-weight:bold;
    ">
      LED BLUE APAGADO
    </div>

    <canvas id="tempChart" width="400" height="200"></canvas>

    <div id="ultima-actualizacion">Última actualización: <span id="fecha">--</span></div>
  </div>

  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <script>
    const ctx = document.getElementById('tempChart').getContext('2d');
    const tempChart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [],  // aquí guardaremos los tiempos
        datasets: [{
          label: 'Temperatura (°C)',
          data: [],
          borderColor: '#ff1900',
          backgroundColor: 'rgba(255, 25, 0, 0.2)',
          tension: 0.3,
          borderWidth: 2,
          pointRadius: 0
        }]
      },
      options: {
        responsive: true,
        scales: {
          y: {
            beginAtZero: false
          }
        },
        plugins: {
          legend: { labels: { color: 'white' } }
        }
      }
    });

    function actualizarDatos() {
      fetch('/datos')
        .then(response => response.json())
        .then(data => {
        
          document.getElementById('temperatura').textContent = data.temperatura;
          document.getElementById('humedad').textContent = data.humedad;
          document.getElementById('conteo').textContent = data.conteo;
          document.getElementById('fecha').textContent = new Date().toLocaleTimeString();

          const indicador = document.getElementById('indicador');

          if (data.mensaje === "BOTON_PRESIONADO") {
            indicador.className = "estadoBoton activo";
            indicador.textContent = "STOP";
          } 
          else {
            indicador.className = "estadoBoton inactivo";
            indicador.textContent = "RUN";
          }

        // === Actualizar gráfica ===
        const tiempo = new Date().toLocaleTimeString();
        tempChart.data.labels.push(tiempo);
        tempChart.data.datasets[0].data.push(data.temperatura);

        if (tempChart.data.labels.length > 100) { // Máximo 20 puntos visibles
          tempChart.data.labels.shift();
          tempChart.data.datasets[0].data.shift();
        }

        tempChart.update();

        });
    }

    function enviarComando(cmd) {
      fetch(`/enviar?cmd=${cmd}`)
        .then(response => response.text())
        .then(data => {
          console.log("Comando enviado:", data);

          if (cmd === "BOTON_WEB_1") {
            const leyenda = document.getElementById('estado-led-rojo');
            
            if (leyenda.textContent.includes("APAGADO")) {
              leyenda.textContent = "LED ROJO ENCENDIDO";
              leyenda.style.color = "#ff1900ff";
            } 
            else {
              leyenda.textContent = "LED ROJO APAGADO";
              leyenda.style.color = "#404141ff";
            }
          }

          if (cmd === "BOTON_WEB_2") {
            const leyenda = document.getElementById('estado-led-azul');
            
            if (leyenda.textContent.includes("APAGADO")) {
              leyenda.textContent = "LED AZUL ENCENDIDO";
              leyenda.style.color = "#0c22ebff";
            } 
            else {
              leyenda.textContent = "LED AZUL APAGADO";
              leyenda.style.color = "#404141ff";
            }
          }
        })
        .catch(err => console.error("Error:", err));
    }

    setInterval(actualizarDatos, 1000);
    actualizarDatos();
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

// Manejador de los datos en formato JSON
void handleDatos() {
  String json = "{";
  json += "\"temperatura\":" + String(temperatura) + ",";
  json += "\"humedad\":" + String(humedad) + ",";
  json += "\"conteo\":" + String(conteo) + ",";
  json += "\"mensaje\":\"" + state_button + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

// Manejador de envío de comandos al Arduino UNO
void handleSend() {
  
  // lee ?cmd=BOTON_WEB_1 o BOTON_WEB_2
  String cmd = server.arg("cmd");
  Serial.print("Comando recibido en Web: ");
  Serial.println(cmd);

  if (cmd == "BOTON_WEB_1") {
    Serial2.println("{\"cmd\":\"BOTON_WEB_1\"}");
  }
  else if (cmd == "BOTON_WEB_2") {
    Serial2.println("{\"cmd\":\"BOTON_WEB_2\"}");
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX_, TX_);
  delay(1000);
  Serial.println("ESP32 - ESCLAVO");

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Fail!");
  }
  Serial.println("\nConectado!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/datos", handleDatos);
  server.on("/enviar", handleSend);
  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  if (Serial2.available()) {
    String json_str = Serial2.readStringUntil('\n');
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, json_str);

    if (!error) {
      temperatura = doc["t"];
      humedad = doc["h"];
      conteo = doc["btn"];
      boton = doc["btn2"];

      if (boton == 1) {
        state_button = "BOTON_PRESIONADO";
      } else {
        state_button = "BOTON_LIBERADO";
      }

    }

    // Serial.println(temperatura);
    // Serial.println(humedad);
    // Serial.println(boton);
    Serial.println(json_str);
  }

  server.handleClient();
  // delay(500);
}