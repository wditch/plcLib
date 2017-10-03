#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Repeating pulse using a pair of linked on-delay timers

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)


   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned long TIMER0 = 0;  // Variable to hold elapsed time for Timer 0
unsigned long TIMER1 = 0;  // Variable to hold elapsed time for Timer 1

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0 (enable)
  andNotBit(Y0);           // And with inverted output
  timerOn(TIMER0, 900);    // 900 ms (0.9 s) delay
  set(Y0);                 // Set Output 0 on time-out

  in(X0);                  // Read Input 0 (enable)
  andBit(Y0);              // And with output
  timerOn(TIMER1, 100);    // 100 ms (0.1 s) delay
  reset(Y0);               // Reset Output 0 on time-out
}