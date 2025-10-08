#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeSansBold18pt7b.h>    // Fuente grande
#include <Fonts/FreeSansBold24pt7b.h>    // Fuente enorme
#include <Fonts/FreeSans9pt7b.h>         // Fuente pequeña

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  // Definiciones de los pines para la pantalla
  #define TFT_CS    D2      // Pin CS de la pantalla (Chip Select)
  #define TFT_RST   D4      // Pin RESET de la pantalla (Reset)
  #define TFT_DC    D1      // Pin DC (Data/Command)
  // #define MOSI      D7      // Pin MOSI para SPI (también puede ser etiquetado como SDA en la pantalla)
  // #define SCK       D5      // Pin SCK para SPI

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// Resolución del display
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

constexpr int SENSOR = 2;
float TEMP;
float HUMD;

DHT dht(SENSOR, DHT11);

void setup() {
  tft.initR(INITR_BLACKTAB); // Inicialización del ST7735
  tft.setRotation(0);        // Orientación horizontal
  tft.fillScreen(ST77XX_BLACK); // Limpia la pantalla
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 10);
  tft.println("Weather");
  // put your setup code here, to run once:
  // Serial.begin(9600);
  dht.begin();
  
  // tft.drawLine(0, 25, tft.width(), 25, ST7735_BLUE);

}

void show_measures() {
  // tft.fillScreen(ST77XX_BLACK); // Limpia la pantalla
  // tft.setFont(&FreeSansBold18pt7b);
  // tft.setTextColor(ST7735_YELLOW);
  // tft.setCursor(3, 40);
  // tft.println("T:");

  // tft.setFont(&FreeSansBold18pt7b);  // Fuente enorme
  // tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(5, 30);
  tft.print(TEMP, 1);
  tft.setTextSize(2);
  tft.println(" C");

  // tft.setCursor(10, 50);
  // tft.println(HUMD, 1);
  
  // Símbolo °C más pequeño
  // tft.setFont(&FreeSans9pt7b);
  // tft.setCursor(108, 30);
  // tft.print(" C");
}

void loop() {
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  TEMP = dht.readTemperature();
  HUMD = dht.readHumidity();

  if (isnan(TEMP) || isnan(HUMD)) {
    // Serial.println("Error data");
    return;
  }


  show_measures();

  // Serial.print("Temp: ");
  // Serial.println(TEMP);
  // Serial.println("°C");

  
  tft.setTextSize(4);
  tft.setCursor(40, 100);
  tft.print(millis()/1000);
  delay(10);
}
