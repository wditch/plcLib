#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   PWM (Pulse Width Modulation) - Analogue control of a PWM output

   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();      // Setup inputs and outputs
}

void loop() {
  inAnalog(X0);    // Read Analogue Input 0
  outPWM(Y0);      // Send to Output 0 as PWM waveform
}


