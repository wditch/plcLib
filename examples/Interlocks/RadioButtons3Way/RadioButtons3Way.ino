#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Using Set and Reset commands to create a 3-way radio button array

   Note: With this simple design, a single output is selected by momentariy
         pressing the corresponding input. However, multiple outputs are
		 repeatedly enabled and disabled if more than one input is
		 simultaneously activated. Consider using a 1-shot pulse or
		 interlock-based design if this is an issue.

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();          // Setup inputs and outputs
}

void loop() {
  in(X0);              // Read switch connected to Input 0 (Set input)
  set(Y0);             // Set Y0 if X0 = 1 momentarily
  reset(Y1);           // Clear Y1 if X0 = 1 momentarily
  reset(Y2);           // Clear Y2 if X0 = 1 momentarily

  in(X1);              // Read switch connected to X1
  set(Y1);             // Set Y1 if X1 = 1 momentarily
  reset(Y0);           // Clear Y0 to 0 if X1 = 1 momentarily
  reset(Y2);           // Clear Y2 to 0 if X1 = 1 momentarily

  in(X2);              // Read switch connected to X2
  set(Y2);             // Set Y2 if X2 = 1 momentarily
  reset(Y0);           // Clear Y0 to 0 if X2 = 1 momentarily
  reset(Y1);           // Clear Y2 to 0 if X2 = 1 momentarily
}