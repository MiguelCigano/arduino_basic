
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>


// Instancia de objeto y dirección
LiquidCrystal_I2C lcd_20(0x20,16,2); 


// Definición de pines

#define LED_L  13  // define LED_L al pin 13 o led l de la targeta nano
#define BOTON1  11 // define BOTON1 al pin 11
#define BOTON2  12 // define BOTON2 al pin 12         


int ESTADO_BOTON1=0;
int ESTADO_BOTON2=0;

// Variables de Lorezn Euler

float roo=10.0;
float r=28.0;
float b=2.66667;
float CI_X = -8.123456;
float CI_Y=-8.567898;
float CI_Z=24.432123; 

float VAL_ANT_X=0;
float VAL_ANT_Y=0;
float VAL_ANT_Z=0;
float tao=0.005;
float VAL_X=0;
float VAL_Y=0;
float VAL_Z=0;

float x_act_pos=0; // Condicion inicial del estado x
float y_act_pos=0; // Condicion inicial del estado y
float z_act_pos=0; // Condicion inicial del estado y

float x_act_01=0;
float x_12bit=0;
unsigned int x_12bit_int=0;

float y_act_01=0;
float y_12bit=0;
unsigned int y_12bit_int=0;

float z_act_01=0;
float z_12bit=0;
unsigned int z_12bit_int=0;

byte buffer[3];



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
  lcd_20.print("3D Lorenz Euler"); 
  lcd_20.setCursor(0,1);
  lcd_20.print("        "); 

	Serial.begin(9600); // inicializar comunicacion serial 

	VAL_X = CI_X;
	VAL_Y = CI_Y;
	VAL_Z = CI_Z;

	VAL_ANT_X = VAL_X;
	VAL_ANT_Y = VAL_Y;
	VAL_ANT_Z = VAL_Z;

    Wire.begin(); // inicializar comunicacion I2C

}

void loop()
{

					
			VAL_X= VAL_ANT_X + (tao * roo * (VAL_ANT_Y - VAL_ANT_X));
			VAL_Y= VAL_ANT_Y + (tao * ((r * VAL_ANT_X) - VAL_ANT_Y - (VAL_ANT_X * VAL_ANT_Z)));
			VAL_Z= VAL_ANT_Z + (tao * ((VAL_ANT_X * VAL_ANT_Y) - (b * VAL_ANT_Z)));	

			VAL_ANT_X = VAL_X;
			VAL_ANT_Y = VAL_Y;
			VAL_ANT_Z = VAL_Z;

			Serial.print(VAL_Z,2);  // imprimir el valor del estado en terminar virtual
			Serial.print(",");     //Escribe en monitor una coma
					
			//delay(10); // retardo en ms

			// de acuerdo con MATLAB, se le suma el valor minimo
			 x_act_pos =  VAL_X + 18; // segun datos de MATLAB
			 y_act_pos =  VAL_Y + 23; // segun datos de MATLAB
			 z_act_pos =  VAL_Z + 9; // segun datos de MATLAB

			// convertir valores a positivos, despues de 0 1, despues de 0-4095 
			x_act_01 =  x_act_pos / 40.0; // segun datos de MATLAB
			x_12bit = round( x_act_01 * 4095.0); // ejemplo: 3992.3
            x_12bit_int= (unsigned int)x_12bit; // conertir a entero sin signo, de12 bits: ejemplo  3992 (dec) o 1111 1001 1000

			y_act_01 =  y_act_pos / 50.0; // segun datos de MATLAB
			y_12bit = round(y_act_01 * 4095.0); // ejemplo: 3992.3
            y_12bit_int= (unsigned int)y_12bit; // conertir a entero sin signo, de12 bits: ejemplo  3992 (dec) o 1111 1001 1000

			z_act_01 =  z_act_pos / 60.0; // segun datos de MATLAB
			z_12bit = round(z_act_01 * 4095.0); // ejemplo: 3992.3
            z_12bit_int= (unsigned int)z_12bit; // conertir a entero sin signo, de12 bits: ejemplo  3992 (dec) o 1111 1001 1000

			// para datos de x:
			buffer[0] = x_12bit_int >> 4;  // 8 MSB data de 1111 1001 1000 queda 1111 1001 
			buffer[1] = x_12bit_int << 4;  // 4 LSB data de 1111 1001 1000 queda 1001 1000

			// para datos de y:
			buffer[2] = y_12bit_int >> 4;  // 8 MSB data
			buffer[3] = y_12bit_int << 4;  // 4 LSB data

			// para datos de z:
			buffer[4] = z_12bit_int >> 4;  // 8 MSB data
			buffer[5] = z_12bit_int << 4;  // 4 LSB data

			//Serial.println(x_12bit_int,DEC);  // imprimir el valor del estado en terminar virtual
			//Serial.println(x_12bit_int,BIN);  // imprimir el valor del estado en terminar virtual
			//Serial.print(",");     //Escribe en monitor una coma
			//Serial.println(buffer[0],BIN);  // imprimir el valor del estado en terminar virtual	
			//Serial.println(buffer[1],BIN);  // imprimir el valor del estado en terminar virtual

			// Convertidor Digital Analogico 12 bit: seleccionar dos de los tres estados a visualizar: buffer 0 y 1 para x, 2 y 3 para y, 4 y 5 para z

		  Wire.beginTransmission(0x60);    // 1er byte: direccion esclavo
		  Wire.write(0x40);                        // 2do byte: comando escritura al DAC
		  Wire.write(buffer[0]); //  
		  Wire.write(buffer[1]); //  
		  Wire.endTransmission();   // bit stop


		  Wire.beginTransmission(0x61);    // 1er byte: direccion esclavo
		  Wire.write(0x40);                        // 2do byte: comando escritura al DAC
		  Wire.write(buffer[4]); //  
		  Wire.write(buffer[5]); //  
		  Wire.endTransmission();   // bit stop

}   

  // Funciones externas 


  


