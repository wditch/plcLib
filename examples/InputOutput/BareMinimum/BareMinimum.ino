#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Bare Minimum - Single bit digital input and output

   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  in(X0);      // Read Input 0
  out(Y0);     // Send to Output 0
}