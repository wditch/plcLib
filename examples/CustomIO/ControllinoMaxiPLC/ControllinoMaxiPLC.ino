#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Controllino Maxi PLC - Use of default pin names and numbers
   Product information: http://controllino.cc
   
   Connections:
   Inputs connected to pins A0 - A9, plus interrupts IN0 and IN1
   Digital outputs connected to pins D0 to D11
   Relay outputs connected to pins R0 to R9

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
   
*/

// Pins A0 - A9 are configured automatically

// Interrupt pins
const int IN0 = 18;
const int IN1 = 19;

const int D0 = 2;
const int D1 = 3;
const int D2 = 4;
const int D3 = 5;
const int D4 = 6;
const int D5 = 7;
const int D6 = 8;
const int D7 = 9;
const int D8 = 10;
const int D9 = 11;
const int D10 = 12;
const int D11 = 13;

const int R0 = 22;
const int R1 = 23;
const int R2 = 24;
const int R3 = 25;
const int R4 = 26;
const int R5 = 27;
const int R6 = 28;
const int R7 = 29;
const int R8 = 30;
const int R9 = 31;

void setup() {
  customIO();        // Setup inputs and outputs for Controllino PLC
}                    // (See IO tab for details)

void loop() {        // Sample code follows - replace as required
  in(A0);            // Read Input A0 and send to Output D0
  out(D0);
}
