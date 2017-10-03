#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Digital Input Output - Single bit I/O in normal and inverted forms

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - switch connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/
   
void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  in(X0);      // Read Input 0
  out(Y0);     // Send to Output 0

  inNot(X1);   // Read Input 1 (inverted)
  out(Y1);     // Send to Output 1

  in(X2);      // Read Input 2
  outNot(Y2);  // Send to Output 2 (inverted)
  
  inNot(X3);   // Read Input 3 (inverted) and send to Output 3 (inverted)
  outNot(Y3);  // (The double negative cancels out)
}
