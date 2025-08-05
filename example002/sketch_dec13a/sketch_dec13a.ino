#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
// Definiciones de los pines para la pantalla
  #define TFT_CS    D2      // Pin CS de la pantalla (Chip Select)
  #define TFT_RST   D4      // Pin RESET de la pantalla (Reset)
  #define TFT_DC    D1      // Pin DC (Data/Command)
  //#define MOSI      D7      // Pin MOSI para SPI (también puede ser etiquetado como SDA en la pantalla)
 // #define SCK       D5      // Pin SCK para SPI

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


// Resolución del display
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// Variables para las ecuaciones de Lorenz
float x = 0.1, y = 0, z = 0; // Condiciones iniciales
float dt = 0.01;             // Paso de tiempo
float sigma = 10.0, rho = 28.0, beta = 8.0 / 3.0; // Parámetros

void setup() {
  // Inicialización del display
  tft.initR(INITR_BLACKTAB); // Inicialización del ST7735
  tft.setRotation(1);        // Orientación horizontal
  tft.fillScreen(ST77XX_BLACK); // Limpia la pantalla
}

void loop() {
  // Calcula el siguiente paso de las ecuaciones de Lorenz
  float dx = sigma * (y - x) * dt;
  float dy = (x * (rho - z) - y) * dt;
  float dz = (x * y - beta * z) * dt;
  
  x += dx;
  y += dy;
  z += dz;

  // Mapear los valores al tamaño de la pantalla
  int xPixel = map(x * 2, -30, 30, 0, TFT_WIDTH);
  int yPixel = map(y * 2, -30, 30, 0, TFT_HEIGHT);

  // Dibuja el punto en la pantalla
  uint16_t color = tft.color565((int)(z * 10) % 200, 80, 200); // Color dinámico según z
  tft.drawPixel(xPixel, yPixel, color);

  delay(2); // Pequeño retraso para suavizar el efecto
}

