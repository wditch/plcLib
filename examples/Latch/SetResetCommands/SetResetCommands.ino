#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Using Set and Reset commands to create a Set-Reset Latch

   Connections:
   Input - Set - switch connected to input X0 (Arduino pin A0)
   Input - Reset - switch connected to input X1 (Arduino pin A1)
   Output - Q - LED connected to output Y0 (Arduino pin 3)
   Output - NotQ - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

void setup() {
  setupPLC();          // Setup inputs and outputs
}

void loop() {
  in(X0);              // Read switch connected to Input 0 (Set input)
  set(Y0);             // Set Y0 to 1 if X0 = 1, leave Y0 unaltered otherwise

  in(X1);              // Read switch connected to X1
  reset(Y0);           // Clear Y0 to 0 if X1 = 1, leave Y0 unaltered otherwise
}