#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields M-Duino 19R IO PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs 
     I00 - I05 (B Zone)

   Outputs
     Q00 - Q02 (B Zone)
     R1-R8     (B Zone)

   Software and Documentation:
   https://github.com/wditch/plcLib
   
*/

// B Zone Inputs
const int I00 = 2;       // Interrupt 0
const int I01 = 3;       // Interrupt 1
const int I02 = A0;
const int I03 = A1;
const int I04 = A2;
const int I05 = A3;

// B Zone Outputs
const int Q00 = 4;
const int Q01 = 5;
const int Q02 = 6;

// B Zone Relay Outputs
const int R01 = 23;
const int R02 = 22;
const int R03 = 25;
const int R04 = 24;
const int R05 = 40;
const int R06 = 39;
const int R07 = 38;
const int R08 = 37;

void setup() {
  customIO();          // Setup inputs and outputs for Industrial Shields M-Duino 19R IO PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I00);             // Read Input I00 and send to Output Q00
  out(Q00);

  serialMonitor("MDuino19RelayPLC");   // Enable remote I/O monitoring via the serial port
}
