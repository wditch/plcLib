#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Inverted Input Logic - Boolean logic operations using inverted inputs
                          (equivalent to normally closed input switches)

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output - ANDed output - LED connected to output Y0 (Arduino pin 3)
   Output - ORed output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/
*/

void setup() {
  setupPLC();      // Setup inputs and outputs
}

void loop() {
  in(X0);          // Read Input 0
  andNotBit(X1);   // AND with Input 1 (inverted)
  out(Y0);         // Send result to Output 0

  in(X0);          // Read Input 0
  orNotBit(X1);    // OR with Input 1 (inverted)
  out(Y1);         // Send result to Output 1
}


