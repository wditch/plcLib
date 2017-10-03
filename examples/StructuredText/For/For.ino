#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   FOR loop - Manually created 'PWM' waveform (very primitive)

   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();                               // Setup inputs and outputs
}

void loop() {

  for(unsigned int i = 0; i <= 1023; i++) { // Loop from i=0 to i=1023 in unit steps
    inAnalog(i);                            // Read count as an 'analogue' value
    compareGT(X0);                          // Compare with Analogue Input 0
    out(Y0);                                // Output comparison result to Output 0
  }
}
