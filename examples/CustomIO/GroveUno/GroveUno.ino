#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   SeeedStudio Grove Base Shield - Use of Grove pin names and numbers
   Product information: http://www.seeedstudio.com/
   
   Connections:
   Inputs
     A0 - A4

   Digital pins (Inputs / Outputs)
     D2 - D9

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
   
   Pin names A0 - A4 are defined automatically

*/

// Configure digital pin names
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
const int D8 = 8;
const int D9 = 9;


void setup() {
  customIO();        // Setup inputs and outputs for Grove Base Shield
}                    // (See IO tab for details)

void loop() {        // Sample code follows - replace as required
  in(A0);            // Read Input A0 and send to Output D2
  out(D2);
}
