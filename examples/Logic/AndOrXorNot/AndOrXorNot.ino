#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   AND, OR, XOR and Not - Basic Boolean Logic Functions

   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Output - ANDed Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Output - ORed Output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)
   Output - XORed Output - LED connected to output Y2 (Arduino pin 6 / Tinkerkit O3)
   Output - Inverted Output - LED connected to output Y3 (Arduino pin 9 / Tinkerkit O2)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  in(X0);      // Read Input 0
  andBit(X1);  // AND with Input 1
  out(Y0);     // Send result to Output 0

  in(X0);      // Read Input 0
  orBit(X1);   // OR with Input 1
  out(Y1);     // Send result to Output 1
  
  in(X0);      // Read Input 0
  xorBit(X1);  // XOR with Input 1
  out(Y2);     // Send result to Output 2
  
  in(X0);      // Read Input 0
  outNot(Y3);  // Send inverted result to Output 3
}


