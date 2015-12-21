#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields Ardbox Analog PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs connected to pins I00 to I09
   Outputs connected to pins Q00 to Q09

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
   
*/

const int I00 = 2;
const int I01 = 12;
const int I02 = 8;
const int I03 = 4;
const int I04 = A5;
const int I05 = A4;
const int I06 = A3;
const int I07 = A2;
const int I08 = A1;
const int I09 = A0;
const int Q00 = 13;
const int Q01 = 11;
const int Q02 = 10;
const int Q03 = 9;
const int Q04 = 6;
const int Q05 = 5;
const int Q06 = 3;
const int Q07 = 7;
const int Q08 = 1;
const int Q09 = 0;

void setup() {
  customIO();        // Setup inputs and outputs for Ardbox Analog PLC
}                    // (See IO tab for details)

void loop() {        // Sample code follows - replace as required
  in(I00);           // Read Input I00 and send to Output Q00
  out(Q00);
}
