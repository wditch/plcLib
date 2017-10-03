#define noPinDefs         // Disable default pin definitions (X0, X1, ..., Y0, Y1, ...)
#include <plcLib.h>       // Load the PLC library
#include <TinkerKit.h>    // Load the TinkerKit library (Disable if not needed)

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Tinkerkit Compatible - Use of Tinkerkit pin names and numbers
   Product information (software library): https://github.com/TinkerKit/TinkerKit
   
   (Including the Tinkerkit library allows Tinkerkit input/output pin names
    and numbers to be used - I0-I5/O0-O5 for the Arduino Uno.)

   Connections:
   Input - switch connected to input I0 (Arduino pin A0)
   Input - switch connected to input I1 (Arduino pin A1)
   Input - switch connected to input I2 (Arduino pin A2)
   Input - switch connected to input I3 (Arduino pin A3)
   Input - switch connected to input I4 (Arduino pin A4)
   Input - switch connected to input I5 (Arduino pin A5)
   Output - LED connected to output O0 (Arduino pin 11)
   Output - LED connected to output O1 (Arduino pin 10)
   Output - LED connected to output O2 (Arduino pin 9)
   Output - LED connected to output O3 (Arduino pin 6)
   Output - LED connected to output O4 (Arduino pin 5)
   Output - LED connected to output O5 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib
   
   The following pin definitions will not be needed if the TinkerKit library is
   loaded at the top of this file - otherwise uncomment the following lines

const int I0 = A0;
const int I1 = A1;
const int I2 = A2;
const int I3 = A3;
const int I4 = A4;
const int I5 = A5;

const int O0 = 11;
const int O1 = 10;
const int O2 = 9;
const int O3 = 6;
const int O4 = 5;
const int O5 = 3;

*/

void setup() {
  customIO();          // Setup inputs and outputs for TinkerKit Base Shield (See IO tab)
  Serial.begin(9600);  // Enable serial port (needed for serial IO monitor)
}

void loop() {          // Sample code follows - replace as required
  in(I0);              // Read Input 0 and send to Output 0
  out(O0);

  serialMonitor("TinkerkitUno");   // Enable remote I/O monitoring via the serial port
}
