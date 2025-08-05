
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

// *** CREAR OBJETO LCD Y DIRECCION, 16X2 ***
LiquidCrystal_I2C lcd_20(0x20,16,2); 


// *** DEFINICIONES DE PINES DEL ARDUINO ***
#define LED_L  13  // define LED_L al pin 13 o led l de la targeta nano
#define BOTON1  11 // define BOTON1 al pin 11
#define BOTON2  12 // define BOTON2 al pin 12         

// BOTONES DE PRESIONAR:
int ESTADO_BOTON1=0;
int ESTADO_BOTON2=0;
 
// VARIABLES DE MAPAS CAOTICOS
double a=0.9, b=-0.6013, c=2, d=0.5;
double CI_X=0.15, CI_Y=0.1; 

double VAL_ANT_X=0, VAL_ANT_Y=0;
double VAL_X=0,VAL_Y=0;

double X_a=0, Y_a=0;
double X_b=0, Y_b=0;
int X_int =0, Y_int =0;

void setup() 
{
	  // inicializar LCDs
	 lcd_20.init();
	 // encender la luz de fondo.
	 lcd_20.backlight();
	 // limpiar LCDs.
	 lcd_20.clear();
	  
	 // definir puertos de entrada 
	 pinMode(BOTON1, INPUT); // Define BOTON1 de tarjeta entrada ACTIVO ALTO.
	 pinMode(BOTON2, INPUT); // Define BOTON1 de tarjeta entrada ACTIVO ALTO

	 // definir puertos de salida (no es necesario)  
	 pinMode(LED_L, OUTPUT); // Define led de tarjeta salida.

	 // asignar apagado a focos y buzzer.
	 digitalWrite(LED_L, LOW);

	 // asignar variables a pantallas LCD.
	 lcd_20.setCursor(0,0);
	 lcd_20.print("Tinker 2 D"); 
	 lcd_20.setCursor(0,1);
	 lcd_20.print("        "); 

	 Serial.begin(9600); // inicializar comunicacion serial 
	 Wire.begin(); // inicializar comunicacion I2C
}

// *** INICIO CICLO INFINITO ***
void loop()
{
	 VAL_X = CI_X; 
	 VAL_Y = CI_Y;
	 for (int i = 0; i <= 9981; i++) 
	 {
		  VAL_ANT_X = VAL_X; // actualizar estado previo con actual x
		  VAL_ANT_Y = VAL_Y; // actualizar estado previo con actual y
		  
		  VAL_X = (VAL_ANT_X *VAL_ANT_X ) - (VAL_ANT_Y  * VAL_ANT_Y) + (a*VAL_ANT_X ) + (b*VAL_ANT_Y); // tinkerbell estado actual x
		  VAL_Y = (2 * VAL_ANT_X * VAL_ANT_Y) + (c * VAL_ANT_X) + (d * VAL_ANT_Y); // tinkerbell estado actual y
		  
		  
		  Serial.print(VAL_X,15);  // imprimir el estado x en terminal virtual
		  Serial.print(","); 
		  //Serial.print(VAL_Y,15);  // imprimir el estado y en terminal virtual
		  //Serial.print(",");

		  
		  // convertir valor 0-5 a 0-4095 -> voltaje de 0-5 volts segun hoja datos con Vdd 5Vdc		  
		  X_b=VAL_X+3; 
		  Y_b=VAL_Y+3;
		  X_a= round( (X_b * 4095.0)/5 ); // ejemplo: 3992.3=3992.0
		  X_int = (unsigned int)X_a; // convertir a entero sin signo, de 12 bits: ejemplo  3992 (dec) o 1111 1001 1000
		  Y_a = round( (Y_b * 4095.0)/5 ); 
		  Y_int = (unsigned int)Y_a;
		  

		  Wire.beginTransmission(0x60);    // 1er byte
		  Wire.write(0x40);                        	// 2do byte
		  Wire.write(X_int >> 8); 			// 3er byte 
		  Wire.write(X_int & 255); 		// 4to byte 
		  Wire.endTransmission();   // bit stop

	 }
}