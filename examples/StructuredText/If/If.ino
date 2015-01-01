#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   IF - Conditional control of a PWM output
   
   LED brightness may be varied using the potentiometer, but only when X0 is pressed.
   Previous PWM output is displayed otherwise. 

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
}

void loop() {
  myVar = in(X0);         // Read digital Input 0, storing result in user variable

  if (myVar == 1) {       // Vary PWM, if enabled
    inAnalog(X1);         // Read Analogue Input 1
    outPWM(Y0);           // Send to Output 0 as PWM waveform
  }
}

