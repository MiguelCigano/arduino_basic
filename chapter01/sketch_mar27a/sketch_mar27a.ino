#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del módulo (normalmente 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
    // Wire.begin(20, 21);  // Configurar I2C (SDA=D2, SCL=D1)
    lcd.init();        // Inicializar LCD
    lcd.backlight();   // Encender retroiluminación

    lcd.setCursor(0, 0);
    lcd.print("Hola desde set up!");
}

void loop() {
    lcd.setCursor(0, 1);
    lcd.print("jajaja");
    delay(1000);
}
// // LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// void setup()
// {
//   // Wire.begin(4, 5);  // Configurar I2C (SDA=D2, SCL=D1)
//   Wire.begin(); 
//   lcd.init();        // Inicializar LCD
//   lcd.backlight();   // Encender retroiluminación
//   // Indicar a la libreria que tenemos conectada una pantalla de 16x2
//   // lcd.begin(16, 2);
//   // Mover el cursor a la primera posición de la pantalla (0, 0)
//   lcd.home ();
//   // Imprimir "Hola Mundo" en la primera linea
//   lcd.print("Hola Mundo");
//   // Mover el cursor a la segunda linea (1) primera columna
//   lcd.setCursor ( 0, 1 );
//   // Imprimir otra cadena en esta posicion
//   lcd.print("ESP8266");
//   // Esperar un segundo
//   delay(1000);
// }
 
// void loop()
// {
//   // EN EL CICLO PRINCIPAL SOLAMENTE RECORREMOS EL MENSAJE DE UN LADO A OTRO
//   // Variable para conteo de ciclos
//   int i;
 
//   // Desplazar la pantalla a la derecha 2 veces
//   for ( int i = 0; i < 5; i++ ) {
//     lcd.scrollDisplayRight();
//     delay (1000);
//   }
 
//   // Desplazar la pantalla a la izquierda 2 veces
//   for ( int i = 0; i < 5; i++ ) {
//     lcd.scrollDisplayLeft();
//     delay (1000);
//   }
// }


// void setup() {
//     Serial.begin(9600); // Inicia la comunicación serial
// }

// void loop() {
//     Serial.println("Arduino Mega funcionando!");
//     delay(1000); // Envía un mensaje cada segundo
// }