#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Complex Logic - Solving multiple branch Boolean Logic circuits by using
                   variable(s) to hold temporary calculation results

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - switch connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)

   Equivalent Ladder Logic Circuit:
   |                                |
   |         X0    X1               |
   |     |---| |---|/|---|          |
   |     |               |    Y0    |
   |-----|               |---(  )---|
   |     |   X2    X3    |          |
   |     |---| |---| |---|          |
   |                                |
   |                                |

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned int AUX0;  // AUX0 variable holds top rung temporary result

void setup() {
  setupPLC();       // Setup inputs and outputs
}

void loop() {
                    // Solve first branch
  in(X0);           // Read Input 0
  andNotBit(X1);    // AND with inverted Input 1
  out(AUX0);        // Use auxiliary variable AUX0 to store first branch result
  
                    // Solve second branch
  in(X2);           // Read Input 2
  andBit(X3);       // AND with Input 3
  orBit(AUX0);      // OR with result from first branch (AUX0)
  out(Y0);          // Send result to Output 0
}


