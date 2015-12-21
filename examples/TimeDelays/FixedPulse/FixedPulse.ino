#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Fixed Pulse - Activates an output for a fixed period after a momentary input is applied

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output with 2 s pulse - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned long TIMER0 = 0;     // Variable to hold elapsed time for Timer 0

void setup() {
  setupPLC();                 // Setup inputs and outputs
}

void loop() {
  in(X0);                     // Read Input 0
  timerPulse(TIMER0, 2000);   // 2 second pulse
  out(Y0);                    // Output to Output 0

}