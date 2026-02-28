#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// Configuración WiFi
const char* ssid = "IZZI-BA68";
const char* password = "50A5DC2CBA68";

// Sensor DHT
#define DHT_PIN 4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Servidor web en puerto 80
WebServer server(80);

// Variables para los datos
float temperatura = 0;
float humedad = 0;

void handleRoot() {
  // Página HTML completa que se envía al navegador
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Datos DHT11</title>
  <meta charset="UTF-8">
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      background: #f0f0f0;
      margin: 0;
      padding: 20px;
    }
    .container {
      max-width: 400px;
      margin: 0 auto;
      background: white;
      padding: 30px;
      border-radius: 15px;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
    }
    h1 {
      color: #333;
    }
    .dato {
      font-size: 28px;
      margin: 25px 0;
      padding: 20px;
      border-radius: 10px;
    }
    .temp {
      color: #be1300ff;
      background: #aab5e4ff;
    }
    .hum {
      color: #3498db;
      background: #d6eaf8;
    }
    #ultima-actualizacion {
      color: #7f8c8d;
      margin-top: 20px;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>🌡️ Sensor DHT11 - ESP32</h1>
    
    <div class="dato temp">
      🔥 Temperatura: <span id="temperatura">0</span>°C
    </div>
    
    <div class="dato hum">
      💧 Humedad: <span id="humedad">0</span>%
    </div>
    
    <div id="ultima-actualizacion">
      Última actualización: <span id="fecha">--</span>
    </div>
  </div>

  <script>
    function actualizarDatos() {
      fetch('/datos')
        .then(response => response.json())
        .then(data => {
          document.getElementById('temperatura').textContent = data.temperatura;
          document.getElementById('humedad').textContent = data.humedad;
          document.getElementById('fecha').textContent = new Date().toLocaleTimeString();
        })
        .catch(error => console.error('Error:', error));
    }

    // Actualizar cada 2 segundos
    setInterval(actualizarDatos, 1000);
    
    // Cargar datos al iniciar
    actualizarDatos();
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleDatos() {
  // Endpoint que devuelve los datos en JSON
  String json = "{";
  json += "\"temperatura\":" + String(temperatura) + ",";
  json += "\"humedad\":" + String(humedad);
  json += "}";
  
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Conectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // IP que usas en el navegador
  
  // Configurar rutas del servidor
  server.on("/", handleRoot);      // Página principal
  server.on("/datos", handleDatos); // Datos en JSON
  
  server.begin();
  Serial.println("Servidor web iniciado!");
}

void loop() {
  // Lectura de sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (!isnan(temp) && !isnan(hum)) {
    temperatura = temp;
    humedad = hum;
  }
  
  // Manejar clientes web
  server.handleClient();
  delay(1000);
}