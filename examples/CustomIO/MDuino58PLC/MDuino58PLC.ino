#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Industrial Shields M-Duino 58 IO PLC - Use of default pin names and numbers
   Product Information: http://www.industrialshields.com
   
   Connections:
   Inputs 
     I00 - I012 (B Zone)
     I10 - I112 (C Zone)
     I20 - I23, I25-I210 (D Zone)
   Outputs
     Q00 - Q07 (B Zone)
     Q10 - Q17 (C Zone)
     Q20 - Q23, Q25 - Q26 (D Zone)

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

// C Zone Inputs
const int I10 = 27;
const int I11 = 28;
const int I12 = 29;
const int I13 = 30;
const int I14 = 31;
const int I15 = 18;      // Interrupt 5
const int I16 = 19;      // Interrupt 4
const int I17 = A6;
const int I18 = A7;
const int I19 = A8;
const int I110 = A9;
const int I111 = A10;
const int I112 = A11;

// C Zone Outputs
const int Q10 = 41;
const int Q11 = 42;
const int Q12 = 43;
const int Q13 = 44;
const int Q14 = 45;
const int Q15 = 8;
const int Q16 = 10;
const int Q17 = 11;

// D Zone Inputs
const int I20 = 32;
const int I21 = 33;
const int I22 = 34;
const int I23 = 35;
// I24 not connected
const int I25 = 20;      // Interrupt 3
const int I26 = 21;      // Interrupt 2
const int I27 = A12;
const int I28 = A13;
const int I29 = A14;
const int I210 = A15;
// I211 not connected
// I212 not connected

// D Zone Outputs
const int Q20 = 41;
const int Q21 = 42;
const int Q22 = 43;
const int Q23 = 44;
// Q24 not connected
const int Q25 = 8;
const int Q26 = 10;
// Q27 not connected

void setup() {
  customIO();          // Setup inputs and outputs for Industrial Shields M-Duino 58 IO PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I00);             // Read Input I00 and send to Output Q00
  out(Q00);

  serialMonitor("MDuino58PLC");   // Enable remote I/O monitoring via the serial port
}
