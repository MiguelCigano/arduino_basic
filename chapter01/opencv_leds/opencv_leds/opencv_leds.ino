#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS    D2      // Pin CS de la pantalla (Chip Select)
  #define TFT_RST   D4      // Pin RESET de la pantalla (Reset)
  #define TFT_DC    D1      // Pin DC (Data/Command)

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

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);

  tft.initR(INITR_BLACKTAB); // Inicialización del ST7735
  tft.setRotation(0);        // Orientación horizontal
  tft.fillScreen(ST77XX_BLACK); // Limpia la pantalla
  tft.setTextSize(2);
}

void loop() {
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '1') {
      digitalWrite(5, HIGH);
      tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
      tft.setCursor(5, 30);
      tft.println("Red   ");
    } 
    else if (cmd == '0') {
      digitalWrite(5, LOW);
    }
    else if (cmd == '2') {
      digitalWrite(6, HIGH);
      tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
      tft.setCursor(5, 30);
      tft.println("Yellow");
    }
    else if (cmd == '3') {
      digitalWrite(6, LOW);
    }
  }
}
