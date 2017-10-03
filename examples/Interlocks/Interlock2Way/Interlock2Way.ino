#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Using Set and Reset commands to create a 2-way Interlock
   
   Note: With this interlock-based design, the currently active output
         cannot be changed until the corresponding input is released.

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();          // Setup inputs and outputs
}

void loop() {
  in(X0);              // Read switch connected to Input 0 (Set input)
  andNotBit(X1);       // Disable if X1 is active
  set(Y0);             // Set Y0 if X0 = 1 momentarily
  reset(Y1);           // Clear Y1 if X0 = 1 momentarily

  in(X1);              // Read switch connected to X1
  andNotBit(X0);       // Disable if X0 is active
  set(Y1);             // Set Y1 if X1 = 1 momentarily
  reset(Y0);           // Clear Y0 to 0 if X1 = 1 momentarily
}