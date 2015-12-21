#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Using Set and Unset commands with variables to create a Set Reset Latch

   Connections:
   Input - Set - switch connected to input X0 (Arduino pin A0)
   Input - Reset - switch connected to input X1 (Arduino pin A1)
   Output - Q - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int AUX0 = 0; // Auxiliary variable used to hold latch bit

void setup() {
  setupPLC();          // Setup inputs and outputs
}

void loop() {
  in(X0);              // Read switch connected to Input 0 (Set input)
  set(AUX0);           // Set AUX0 to 1 if X0 = 1, leave unaltered otherwise

  in(X1);              // Read switch connected to X1
  unset(AUX0);         // Clear AUX0 to 0 if X1 = 1, leave unaltered otherwise
  
  in(AUX0);            // Read auxiliary variable AUX0
  out(Y0);             // Output to Y0
}