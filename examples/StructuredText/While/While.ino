#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   While - Wait for an input before starting the main scan loop
   
   (Note: The While loop test is at the start of the loop, so it will only
          run if the condition is initially true, repeating until it
          becomes false. This contrasts with the Do While loop, where the
          test is at the end of the loop, causing it to run at least once.
   
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - potentiometer connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int myVar = 0;   // Create a user defined variable and set initial value

void setup() {
  setupPLC();             // Setup inputs and outputs
  
  while (myVar == 0){     // Wait for an input on X0 before continuing
    myVar = in(X0);
  }
}

void loop() {
  inAnalog(X1);           // Read Analogue Input 1
  outPWM(Y0);             // Send to Output 0 as PWM waveform
}

