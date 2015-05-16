#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Set or reset an output using edge-triggered inputs

   Connections:
   Set input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Reset input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Latched output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Pulse setPulse;              // Create a pulse object to set the latch
Pulse resetPulse;            // Create a pulse object to reset the latch

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read switch connected to Input 0 and
  setPulse.inClock();      // connect it to the set pulse clock input

  in(X1);                  // Read switch connected to Input 1 and
  resetPulse.inClock();    // connect it to reset pulse clock input

  setPulse.rising();       // Read rising edge of X0
  set(Y0);                 // Set Y0 to 1 on using rising edge of X0
  
  resetPulse.rising();     // Read rising edge of X1
  reset(Y0);               // Reset Y0 to 0 on using rising edge of X1
}
