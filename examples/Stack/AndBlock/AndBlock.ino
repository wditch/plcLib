#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Logical AND of two series switch groups using Block AND instruction

                     X0                     X2
                ----|  |----           ----|  |----
                |          |           |          |     Y0
            -----          -------------          -----(  )-----
                |    X1    |           |    X3    |
                ----|  |----           ----|  |----		

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - switch connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)


   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Stack stack1;        // Create a single-bit stack with 32 levels

void setup() {
  setupPLC();        // Setup inputs and outputs
}

void loop() {

                     // Calculate First Branch
  in(X0);            // Read switch connected to Input 0
  orBit(X1);         // Logical OR with Input 1
  stack1.push();     // Push temporary result onto the stack

                     // Calculate second branch
  in(X2);            // Read switch connected to Input 2
  orBit(X3);         // Logical OR with Input 3
  
  stack1.andBlock(); // Merge series branches using Block AND
  out(Y0);           // Send result to Output 0

}