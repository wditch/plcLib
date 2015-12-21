#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Latch Command - Set Reset latch with Q and NotQ outputs, based on the 'latch' command

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
  latch(Y0, X1);       // Latch, Q = Output 0, Reset = Input 1
  
  in(Y0);              // Read Q output and generate NotQ on Output 1
  outNot(Y1);          // (These two lines are optional)
}