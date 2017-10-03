#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Controllino Mini PLC - Use of default pin names and numbers
   Product information: http://controllino.cc
   
   Connections:
   Inputs connected to pins AN0 to AN5, plus interrupts IN0 and IN1
   Outputs connected to pins D0 to D7

   Software and Documentation:
   https://github.com/wditch/plcLib
   
*/

const int AN0 = A0;
const int AN1 = A1;
const int AN2 = A2;
const int AN3 = A3;
const int AN4 = A6;
const int AN5 = A7;
const int IN0 = 2;
const int IN1 = 3;
const int D0 = 4;      // also connected to Relay 0
const int D1 = 5;      // also connected to Relay 1
const int D2 = 6;      // also connected to Relay 2
const int D3 = 7;      // also connected to Relay 3
const int D4 = 8;      // also connected to Relay 4
const int D5 = 9;      // also connected to Relay 5
const int D6 = A4;
const int D7 = A5;

void setup() {
  customIO();          // Setup inputs and outputs for Controllino PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {        // Sample code follows - replace as required
  in(AN0);           // Read Input AN0 and send to Output D0
  out(D0);

  serialMonitor("ControllinoMiniPLC");   // Enable remote I/O monitoring via the serial port
}
