#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields Ardbox TCH PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs connected to pins A0 to A5 and pins D0-D3 (Arduino pins 0-3)
   Outputs connected to pins D4 to D11 (Arduino pins 4-11)
   Relay outputs connected to D12/R1 and D13/R2 (Arduino pins 12 and 13)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
   
*/

// Pins A0 - A5 are configured automatically

const int D0 = 0;
const int D1 = 1;
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
const int D8 = 8;
const int D9 = 9;
const int D10 = 10;
const int D11 = 11;
const int D12 = 12;       // Relay 1
const int D13 = 13;       // Relay 2
const int R1 = 12;        // Relay 1
const int R2 = 13;        // Relay 2


void setup() {
  customIO();        // Setup inputs and outputs for Ardbox PNP PLC
}                    // (See IO tab for details)

void loop() {        // Sample code follows - replace as required
  in(A0);            // Read Input A0 and send to Output D2
  out(D2);
}
