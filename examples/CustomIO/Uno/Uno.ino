#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Arduino Uno - Use of default pin names and numbers
   
   Connections:
   Inputs connected to pins A0-A5
   Digital Input/Output pins connected to D0-D13 (pins 0 to 13)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
   
   Pins A0-A5 are available automatically

*/

const int D0 = 0;   // Pin used for serial RX by default
const int D1 = 1;   // Pin used for serial TX by default
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 7;
const int D7 = 7;
const int D8 = 8;
const int D9 = 9;
const int D10 = 10;
const int D11 = 11;
const int D12 = 12;
const int D13 = 13;

void setup() {
  customIO();        // Setup inputs and outputs for Arduino Uno or compatible
}                    // (See IO tab for details)

void loop() {        // Sample code follows - replace as required
  in(A0);            // Read Input A0 and send to Output D2
  out(D2);
}
