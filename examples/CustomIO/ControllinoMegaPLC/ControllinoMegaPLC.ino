#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Controllino Mega PLC - Use of default pin names and numbers
   Product information: http://controllino.cc
   
   Connections:
   Inputs connected to pins A0 - A15, I16 to I18, plus interrupts IN0 and IN1
   Digital outputs connected to pins D0 to D23
   Relay outputs connected to pins R0 to R15

   Software and Documentation:
   https://github.com/wditch/plcLib
   
*/

// Pins A0 - A15 are configured automatically

// Input pins
const int I16 = 38;
const int I17 = 39;
const int I18 = 40;

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
const int D12 = 42;
const int D13 = 43;
const int D14 = 44;
const int D15 = 45;
const int D16 = 46;
const int D17 = 47;
const int D18 = 48;
const int D19 = 49;

// Note: According to the Controllino Mega Pinout V1.1
// pins D20 - D23 have no equivalent Arduino pin numbers


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
const int R10 = 32;
const int R11 = 33;
const int R12 = 34;
const int R13 = 35;
const int R14 = 36;
const int R15 = 37;

void setup() {
  customIO();          // Setup inputs and outputs for Controllino PLC (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {        // Sample code follows - replace as required
  in(A0);            // Read Input A0 and send to Output D0
  out(D0);

  serialMonitor("ControllinoMegaPLC");   // Enable remote I/O monitoring via the serial port
}
