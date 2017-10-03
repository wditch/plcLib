#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Push and Pop values from a single-bit software stack

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - switch connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

Stack stack1;     // Create a single-bit stack with 32 levels

void setup() {
  setupPLC();     // Setup inputs and outputs
}

void loop() {

                  // Push 4 values onto the stack
                  // 1) X0, 2) X1, 3) X2, 4) X3

  in(X0);         // Read Input 0
  stack1.push();  // Push X0 onto the stack

  in(X1);         // Read Input 1
  stack1.push();  // Push X1 onto the stack

  in(X2);         // Read Input 2
  stack1.push();  // Push X2 onto the stack

  in(X3);         // Read Input 3
  stack1.push();  // Push X3 onto the stack

                  // Remove 4 values from the stack and
                  // send to outputs in reverse order
                  // 1) X3->Y0, 2) X2->Y1, 3) X1->Y2, 4) X0->Y3
                  // (a stack is a last-in first-out or LIFO store)

  stack1.pop();   // Remove X3 value from the stack
  out(Y0);        // Send to Output 0

  stack1.pop();   // Remove X2 value from the stack
  out(Y1);        // Send to Output 1

  stack1.pop();   // Remove X1 value from the stack
  out(Y2);        // Send to Output 2
  
  stack1.pop();   // Remove X0 value from the stack
  out(Y3);        // Send to Output 3
}