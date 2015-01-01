#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Digital Input Output - Single bit I/O in normal and inverted forms

   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Input - switch connected to input X2 (Arduino pin A2 / Tinkerkit pin I2)
   Input - switch connected to input X3 (Arduino pin A3 / Tinkerkit pin I3)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)
   Output - LED connected to output Y2 (Arduino pin 6 / Tinkerkit O3)
   Output - LED connected to output Y3 (Arduino pin 9 / Tinkerkit O2)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

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
