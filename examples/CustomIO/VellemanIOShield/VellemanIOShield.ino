#define noPinDefs       // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>     // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Velleman IO Shield Input / Output mapping
   Product information: http://www.velleman.co.uk/

   Connections:
   6 digital inputs D0-D5 (Arduino pins 2, 3, 4, 5, 6 and 7)
   6 analogue inputs A0-A5 (connected to the same Arduino pins)
   6 relay outputs R0-R5 (Arduino pins 8, 9, 10,11, 12 and 13)
   
   
   Note: outPWM() and outServo() commands should not be used with this
         board due to the use of mechanical switch-based relay outputs.

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

  // Define digital input pins
  const int D0 = 2;
  const int D1 = 3;
  const int D2 = 4;
  const int D3 = 5;
  const int D4 = 6;
  const int D5 = 7;
  
  // Analogue pins will use existing names A0 - A5
  
  // Define Relay outputs as R0 - R5
  const int R0 = 8;
  const int R1 = 9;
  const int R2 = 10;
  const int R3 = 11;
  const int R4 = 12;
  const int R5 = 13;

void setup() {
  customIO();        // Setup inputs and outputs for Velleman IO Shield
}                    // (See IO tab for details)

void loop() {	     // Sample code follows - replace as required
  in(D0);            // Read Digital Input 0
  out(R0);           // Send to Relay Output 0 (Relay 1 of 6)
}
