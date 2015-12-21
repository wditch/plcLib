#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   IF Else - Conditional AND / OR logic function
   
   A 2-input OR function is performed if X0 = 1, otherwise a 2-input AND 

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - potentiometer connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int myVar;   // Create a user defined variable and set initial value

void setup() {
  setupPLC();         // Setup inputs and outputs
}

void loop() {
  myVar = in(X0);     // Read digital Input 0, storing result in user variable

  if (myVar == 1) {   // Perform OR if X0 = 1
    in(X1);           // Read Input 1
    orBit(X2);        // OR with Input 2
    out(Y0);          // Send to Output 0
  }
  else {              // Perform AND if X0 = 0
    in(X1);           // Read Input 1
    andBit(X2);       // AND with Input 2
    out(Y0);          // Send to Output 0
  }
}

