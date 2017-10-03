#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Delayed Pulse - Delays an input pulse by 500 ms
   
   Note: The input must remain active for at least 500 ms to enable the output pulse

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output with 500 ms delay - LED connected to output Y0 (Arduino pin 3)
   Output with no delay - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned long TIMER0 = 0;  // Variable to hold elapsed time for Timer 0
unsigned long TIMER1 = 0;  // Variable to hold elapsed time for Timer 1

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0
  timerOn(TIMER0, 500);    // 500 ms ON delay (rising edge)
  timerOff(TIMER1, 500);   // 500 ms OFF delay (falling edge)
  out(Y0);                 // Output to Output 0 (delayed)

  in(X0);                  // Read Input 0
  out(Y1);                 // Output to Output 1 (no delay)
  
}
