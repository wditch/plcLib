#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Turn-on Delay - Delays turning an output on after an input is applied

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output with 2 s delay - LED connected to output Y0 (Arduino pin 3)
   Output with 4 s delay - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned long TIMER0 = 0;  // Variable to hold elapsed time for Timer 0
unsigned long TIMER1 = 0;  // Variable to hold elapsed time for Timer 1

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0
  timerOn(TIMER0, 2000);   // 2 second delay
  out(Y0);                 // Output to Output 0

  in(X1);                  // Read Input 1
  timerOn(TIMER1, 4000);   // 4 second delay
  out(Y1);                 // Output to Output 1
}