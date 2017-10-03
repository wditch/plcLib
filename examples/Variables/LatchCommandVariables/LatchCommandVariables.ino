#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Latch Command with Variables - Latch command using variables to hold temporary values

   Connections:
   Input - Set - switch connected to input X0 (Arduino pin A0)
   Input - Reset - Switch connected to input X1 (Arduino pin A1)
   Output - Q Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

// Temporary Variables:
unsigned int AUX0;        // Latch output variable
unsigned int AUX1;        // Latch reset variable

void setup() {
  setupPLC();             // Setup inputs and outputs
}

void loop() {
  AUX1 = in(X1);          // AUX1 (Reset) controlled by input X1

  in(X0);                 // Read switch connected to Input 0 (Set input - Input 0)
  latch(AUX0, AUX1);	  // Latch command, Output = AUX0, Reset = AUX1 (Input 1)

  in(AUX0);               // Send Q output to output Y0
  out(Y0);
}