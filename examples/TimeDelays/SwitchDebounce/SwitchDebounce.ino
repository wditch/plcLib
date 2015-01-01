#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Switch Debounce - Delays a switch input by 10 ms to remove contact bounce

   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Output - debounced output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned long TIMER0 = 0;  // Define variable used to hold timer 0 elapsed time

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0
  timerOn(TIMER0, 10);     // 10 ms delay
  out(Y0);                 // Output to Output 0
}