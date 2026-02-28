#include <DHT.h>
#include <DHT_U.h>

constexpr int SENSOR = 2;
float TEMP;
float HUMD;

DHT dht(SENSOR, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  TEMP = dht.readTemperature();
  // HUMD = dht.readHumidity();

  if (isnan(TEMP)) {
    Serial.println("Error data");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(TEMP);
  Serial.println("°C");
  delay(500);
}
