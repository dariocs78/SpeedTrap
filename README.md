
# Arduino Speed Trap / Trampa de velocidad con Arduino
v 1.0 - Darío Calvo Sánchez, 2017-2021

ENGLISH / _ESPAÑOL_

<br/>

![Speed trap / Trampa de velocidad](/images/final.jpg)

<br/>

## DESCRIPTION / _DESCRIPCIÓN_

Arduino-based speed measurement device for scale railway models, showing the equivalent "real-life" speed of a train in km/h. It therefore allows a realistic operation of the railroad model, and helps other purposes such as loco decoder programming. Suitable for most popular scales (H0 and N), although code can be easily modified to suit others.

<br/>

_Medidor de velocidad para trenes a escala basado en Arduino. Muestra la velocidad equivalente en km/h a la que tendría a tamaño real, permitiendo una operación realista o la programación de decodificadores. Adaptado a las dos escalas más populares, H0 y N, aunque el código se puede modificar con facilidad a otras. Ver más información e instrucciones detalladas en español en [https://elgajoelegante.com/trenes/trampa.html](https://elgajoelegante.com/trenes/trampa.html)_

<br/>

## REQUIREMENTS / _REQUISITOS_

This sketch requires the public library **SevenSegmentTM1637.h** by Bram Harmsen - @bremme ([https://github.com/bremme/arduino-tm1637](https://github.com/bremme/arduino-tm1637))

As the code is quite simple, it should work fine in practically any Arduino board you may think of. A Nano is a good and cheap option for this purpose.

Hardware required:
- Arduino board
- TM1637 LED display (7-segment, 4-digit)
- 2x reed contacts
- 1 push button (optional)

<br/>

_Este "sketch" requiere la librería pública **SevenSegmentTM1637.h** de Bram Harmsen - @bremme ([https://github.com/bremme/arduino-tm1637](https://github.com/bremme/arduino-tm1637))_

_Dado que el código es muy simple, debería de funcionar sin problemas en cualquier placa Arduino actual. Una Nano es una opción buena y barata para este propósito._

_Material necesario:_
- _Placa Arduino_
- _Display LED de 7 segmentos y 4 dígitos tipo TM1637_
- _2 ampollas reed_
- _1 pulsador (opcional)_

<br/>

## HARDWARE SET-UP / _INSTALACIÓN FÍSICA_

<br/>

![Set-up scheme](/images/assembly_eng.jpg)

<br/>

Install two reed contacts under a straight and levelled track section, separated by the distance indicated in `distancia_cm` value (see "Initial settings" section below). Link the reeds to the Arduino board as follows:

- Connect one of the reeds to Arduino's pins GND and 5.
- Connect the other reed in a similar manner to pins GND and 6.

Should you wish to use other pins, simply modify "reed1" and "reed2" variables (lines 40 and 41 in the code).

If you intend to use the speed trap in both N and H0 railway models, connect a push button to pins 8 and GND at the Arduino board, to change easily between scale settings. Should you want to use another pin, simply modify the variable `selector_escala` (line 42 in the code).

Connect the TM1637 display to the Arduino board as follows:

- Display pin CLK --> Arduino pin 2
- Display pin I/O or DIO --> Arduino pin 3
- Display pin Vcc or 5V --> Arduino pin 5V
- Display pin GND --> Arduino pin GND

Should you want to change these settings, you can do at code line 16, where the display object is defined:

`SevenSegmentTM1637 display( CLK pin, I/O pin )`

Finally, electrically feed the Arduino as you desire (USB power, Vin pin or any other usual method)

<br/>

![Esquema de montaje](/images/montaje_esp.jpg)

<br/>

_Instalar dos ampollas reed bajo la vía en un tramo recto y nivelado, separadas por la distancia indicada en la variable_ `distancia_cm` _(ver "Ajustes iniciales" más abajo). Conectarlas a la placa de Arduino como sigue:_

- _Conectar una de las ampollas a los pines 5 y GND del Arduino._
- _Conectar la otra de forma similar a los pines 6 y GND._

_En el caso de querer usar otros pines, cambiar los valores de las variables_ `reed1` _y_ `reed2` _en las líneas 40 y 41 del código._

_Si se desea usar la trampa tanto en maquetas a escala N como H0, conectar un pulsador a los pines 8 y GND para cambiar cómodamente de escala. En el caso de querer usar otro pin, cambiar el valor correspondiente de la variable_ `selector_escala` _en la línea 42 del código._

_Conectar el display TM1637 al Arduino como sigue:_

- _Pin CLK en el display --> Pin 2 en Arduino_
- _Pin I/O o DIO en el display --> Pin 3 en Arduino_
- _Pin Vcc o 5V en el display --> Pin 5V en Arduino_
- _Pin GND en el display --> Pin GND en Arduino_

_Si se desearan cambiar los pines en el Arduino, habrá que modificar los valores en la definición del objeto del display en la línea 16 del código:_

`SevenSegmentTM1637 display( pin CLK, pin I/O )`

_Finalmente, alimentar eléctricamente el Arduino de la forma preferida (USB, pin Vin o cualquier otro método)_

<br/>

## INITIAL SETTINGS / _AJUSTES INICIALES_

Upload the sketch file "Trampa_de_velocidad-Speed_trap.ino" to the Arduino board. The code is set up by default for an N-scale railway, with reed contacts separated 25 cm apart. Should you wish to change these settings, you need to modify the following parameters:
- Line 25: `distancia_cm` sets up the distance between reed contacts (in cm)
- Line 27: `factor_escala` sets up the scale factor (160 for N or 87 for H0)

LED display brightness is set to 100% by default, but can be modified through parameter `display.setBacklight()` at line 50 in the code.

<br/>

_Subir el código "Trampa_de_velocidad-Speed_trap.ino" a la placa de Arduino. El programa está ajustado de fábrica a escala N y a un tramo de vía con las ampollas reed separadas 25 cm. En el caso de querer cambiar estos ajustes, habría que modificar los siguientes parámetros:_
- _Línea 25: la variable_ `distancia_cm` _define la distancia en centímetros entre las ampollas reed. Es un número real, por lo que admite decimales usando un punto como separación_
- _Línea 27: la variable_ `factor_escala` _define la escala a considerar (160 para N o bien 87 para H0)_

_El brillo del display LED está ajustado de fábrica al 100%, pero se puede modificar a gusto del usuario cambiando el valor del parámetro_ `display.setBacklight()` _en la línea 50 del programa._

<br/>

## INSTRUCTIONS OF USE / _INSTRUCCIONES DE USO_

Once the system is powered on, the display will blink "0000" and show the initial scale setting briefly ("E160" or "E 87"). After that, the display will go to idle waiting for signals from any of the reed contacts.

Put a train on the tracks and ensure the locomotive or one of the cars has a magnet installed beneath its chassis, in order to activate the reed contacts.

The speed trap will work in both directions, no matter what reed contact is activated first. It will get a signal from the first contact, and measure the time until receiving the signal from the other reed. Then it will compute the equivalent speed in km/h considering the scale, and it will show it on the LED display for 2 seconds. Then it will get back to idle state.

Note that once one of the reeds is activated, the system will not accept further inputs from that reed until the other one has been activated. Keep this in mind in case of failure, and reset the Arduino board if required.

When idle, the scale setting can be changed by pushing the corresponding button (if installed)

<br/>

_Una vez se enciende el sistema, el número "0000" parpadeará brevemente en el display, y seguidamente mostrará el ajuste inicial de escala ("E 160" o "E 87"). Después el sistema quedará en reposo a la espera de recibir alguna señal de las ampollas reed._

_Poner en la vía un tren dotado de un pequeño imán en los bajos, ya sea en la locomotora o en uno de los coches, que permitirá activar las ampollas reed._

_La trampa funcionará independientemente del sentido de marcha del tren y de la ampolla que se active primero. Recogerá la señal del primer contacto y medirá el tiempo que pasa hasta que se produzca el contacto en la otra ampolla, calculando entonces la velocidad equivalente considerando la escala. Mostrará la velocidad en km/h el display durante 2 segundos, y después volverá al estado de reposo._

_Es importante notar que una vez se active una de las ampollas, el sistema no aceptará más señales de ese contacto hasta que la otra ampolla se haya activado. Hay que tener esto en cuenta en caso de fallo en la lectura: resetear el Arduino lo solucionará._

_Si se instaló, mientras el sistema esté en reposo podremos actuar sobre el pulsador de cambio de escala._

<br/>

## LICENSE / _LICENCIA_

Trampa de velocidad con Arduino by Dario Calvo Sanchez is licensed under CC BY-NC-SA 4.0. To view a copy of this license, visit [https://creativecommons.org/licenses/by-nc-sa/4.0](https://creativecommons.org/licenses/by-nc-sa/4.0)