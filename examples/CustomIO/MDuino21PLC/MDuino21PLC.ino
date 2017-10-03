#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields M-Duino 21 IO PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs 
     I00 - I012 (B Zone)

   Outputs
     Q00 - Q07 (B Zone)

   Software and Documentation:
   https://github.com/wditch/plcLib
   
*/

// B Zone Inputs
const int I00 = 22;
const int I01 = 23;
const int I02 = 24;
const int I03 = 25;
const int I04 = 26;
const int I05 = 2;      // Interrupt 0
const int I06 = 3;      // Interrupt 1
const int I07 = A0;
const int I08 = A1;
const int I09 = A2;
const int I010 = A3;
const int I011 = A4;
const int I012 = A5;

// B Zone Outputs
const int Q00 = 36;
const int Q01 = 37;
const int Q02 = 38;
const int Q03 = 39;
const int Q04 = 40;
const int Q05 = 4;
const int Q06 = 5;
const int Q07 = 6;


void setup() {
  customIO();          // Setup inputs and outputs for Industrial Shields M-Duino 21 IO PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I07);             // Read Input I07 and send to Output Q07
  out(Q07);

  serialMonitor("MDuino21PLC");   // Enable remote I/O monitoring via the serial port
}
