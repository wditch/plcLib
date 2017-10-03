#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields Ardbox Relay PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs connected to pins I00 to I09
   Outputs connected to pins R1 to R8 and Q00 to Q01

   Software and Documentation:
   https://github.com/wditch/plcLib
   
*/

const int I00 = 2;
const int I01 = 3;
const int I02 = 0;
const int I03 = 1;
const int I04 = A0;
const int I05 = A1;
const int I06 = A2;
const int I07 = A3;
const int I08 = A4;
const int I09 = A5;
const int R1 = 4;
const int R2 = 7;
const int R3 = 8;
const int R4 = 9;
const int R5 = 10;
const int R6 = 11;
const int R7 = 12;
const int R8 = 13;
const int Q00 = 5;
const int Q01 = 6;

void setup() {
  customIO();          // Setup inputs and outputs for Ardbox Relay PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I00);             // Read Input I00 and send to Output R1
  out(R1);

  serialMonitor("ArdboxRelayPLC");   // Enable remote I/O monitoring via the serial port
}
