// Trampa de velocidad con Arduino / Arduino Speed Trap (version 1)
// (Medidor de velocidad para ferrocarriles a escala / Speed measurement for scale railway models)
// Dario Calvo Sanchez, 2017-2021

// Trampa de velocidad con Arduino by Dario Calvo Sanchez is licensed under CC BY-NC-SA 4.0. To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0
// Requires library "SevenSegmentTM1637.h" by Bram Harmsen (@bremme) (https://github.com/bremme/arduino-tm1637)

// Ajustes por defecto: escala N y distancia entre reeds de 25 cm (ver lineas 25 y 27) / Default settings: N-scale, 25 cm between reed contacts (see code lines 25 & 27)


// Libreria y ajustes del display LED TM1637 de cuadro digitos y siete segmentos / 4-digit 7-segment TM1637 LED display library & settings
  //  - Pin CLK: 2
  //  - Pin I/O: 3

#include <SevenSegmentTM1637.h>
SevenSegmentTM1637 display(2, 3);


// Declaracion de variables / Variable declaration:

unsigned long tinicial;
unsigned long tfinal;
float transcurrido;
float segundos;
float distancia_cm = 25.00;               // Distancia entre reeds / Distance between reed contacts
float velocidad_real;
int factor_escala = 160;                  // Valor de escala inicial (N 1:160) / Initial scale setting (N 1:160)
int velocidad_escala;
int contador1 = 0;
int contador2 = 0;
int contadorDisp = 0;
int displayoffset = 0;


// Definicion de pines / Pin assignment:
  //  - Pin del primer reed / First reed: 5
  //  - Pin del segundo reed / Second reed: 6
  //  - Pin del selector de escala / Scale selector button: 8

int reed1 = 5;
int reed2 = 6;
int selector_escala = 8;


// Configuracion del dispositivo / Device set-up:

void setup(){

 display.begin();
 display.setBacklight(100);               // Ajusta brillo del display LED al 100% / Sets display brightness to 100%
 pinMode(reed1, INPUT_PULLUP);
 digitalWrite(reed1, HIGH);
 pinMode(reed2, INPUT_PULLUP);
 digitalWrite(reed2, HIGH);
 pinMode(selector_escala, INPUT_PULLUP);
 digitalWrite(selector_escala, HIGH);

 display.print("0000");
 display.blink();
 delay(500);
 display.clear();
 delay(500);
 display.print("E");
 display.setCursor(1, 1);
 display.print(factor_escala);
 delay(1000);
 display.home();
 display.clear();

}

// Bucle principal / Main loop:

void loop(){

 // Seleccion de escala / Scale selection

 if((contador1 == 0) && (contador2 == 0)) {

     if((digitalRead(selector_escala) == LOW) && (factor_escala == 160)){
      delay(500);
      factor_escala = 87;
      display.print("E");
      display.setCursor(1, 2);
      display.print(factor_escala);
      delay(1000);
      display.home();
      display.clear();
     }

     if((digitalRead(selector_escala) == LOW) && (factor_escala == 87)){
      delay(500);
      factor_escala = 160;
      display.print("E");
      display.setCursor(1, 1);
      display.print(factor_escala);
      delay(1000);
      display.home();
      display.clear();
     }

   }

 // Comprobacion de contactos: si se activa el reed 2... / Contact check: if reed 2 is activated...

 if(digitalRead(reed2) == LOW){

     if((contador1 == 1) && (contador2 == 0)){
      tfinal = millis();
      transcurrido = float(tfinal - tinicial);
      segundos = transcurrido / 1000.;
      contador2 = 1;
     }

     if((contador1 == 0) && (contador2 == 0)){
      tinicial = millis();
      contador2 = 1;
     }

   }

 // ...o si se activa el reed 1 / ...or if reed 1 is activated

 if(digitalRead(reed1) == LOW){

     if((contador2 == 1) && (contador1 == 0)){
      tfinal = millis();
      transcurrido = float(tfinal - tinicial);
      segundos = transcurrido / 1000.;
      contador1 = 1;
     }

     if((contador2 == 0) && (contador1 == 0)){
      tinicial = millis();
      contador1 = 1;
     }

   }

 // Calculo de la velocidad / Speed computing

 if((contador1 == 1) && (contador2 == 1)){

  velocidad_real = distancia_cm / segundos;
  velocidad_escala = int(factor_escala * 0.036 * velocidad_real);

    if(velocidad_escala > 9999 || velocidad_escala < 0){
      display.clear();
      display.print("ERR");
    }

    else{

    // Preparacion y salida al display LED / LED display output arrangement

    if((velocidad_escala >= 100) && (velocidad_escala < 1000)){
      displayoffset = 1;
    }

    if((velocidad_escala >= 10) && (velocidad_escala < 100)){
      displayoffset = 2;
    }

    if((velocidad_escala >= 0) && (velocidad_escala < 10)){
      displayoffset = 3;
    }

    display.clear();
    display.setCursor(1, displayoffset);
    display.print(velocidad_escala);
    display.home();

    }

  delay(2000);                            // Espera 2 s para evitar falsos contactos de otros vehiculos del tren / Waits 2 s to avoid false contacts from other vehicles in the train
  displayoffset = 0;
  contador1 = 0;
  contador2 = 0;
  display.clear();

 }

}
