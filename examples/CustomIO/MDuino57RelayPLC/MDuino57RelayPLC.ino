#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields M-Duino 57R IO PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs 
     I00 - I05 (B Zone)
     I10 - I15 (C Zone)
     I20 - I25 (D Zone)

   Outputs
     Q00 - Q02 (B Zone)
     R01 - R08 (B Zone)
     Q10 - Q12 (C Zone)
     R11 - R18 (C Zone)
     Q20 - Q21 (D Zone)
     R21 - R24, R26 - R28 (D Zone)

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

// C Zone Inputs
const int I10 = 18;      // Interrupt 5
const int I11 = 19;      // Interrupt 4
const int I12 = A6;
const int I13 = A7;
const int I14 = A8;
const int I15 = A9;

// C Zone Outputs
const int Q10 = 8;
const int Q11 = 9;
const int Q12 = 7;

// C Zone Relay Outputs
const int R11 = 28;
const int R12 = 27;
const int R13 = 30;
const int R14 = 29;
const int R15 = 45;
const int R16 = 44;
const int R17 = 43;
const int R18 = 42;

// D Zone Inputs
const int I20 = 20;      // Interrupt 3
const int I21 = 21;      // Interrupt 2
const int I22 = A12;
const int I23 = A13;
const int I24 = A14;
const int I25 = A15;

// D Zone Outputs
const int Q20 = 12;      // see connection "NC*1" in user guide
const int Q21 = 13;
// Q22 is not connected

// D Zone Relay Outputs
const int R21 = 33;
const int R22 = 32;
const int R23 = 35;
const int R24 = 34;
// R25 is not connected
const int R26 = 49;
const int R27 = 48;
const int R28 = 47;

void setup() {
  customIO();          // Setup inputs and outputs for Industrial Shields M-Duino 57R IO PLC (See IO tab )
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I00);             // Read Input I00 and send to Output Q00
  out(Q00);

  serialMonitor("MDuino57RelayPLC");   // Enable remote I/O monitoring via the serial port
}
