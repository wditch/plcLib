#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Analogue Input / PWM Output

   Connections:
   Input - Analogue input or potentiometer connected to input X0 (Arduino pin A0)
   Input - Analogue input or potentiometer connected to input X1 (Arduino pin A1)
   Input - Analogue input or potentiometer connected to input X2 (Arduino pin A2)
   Input - Analogue input or potentiometer connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 with PWM controlled brightness (Arduino pin 3)
   Output - LED connected to output Y1 with PWM controlled brightness (Arduino pin 5)
   Output - LED connected to output Y2 with PWM controlled brightness (Arduino pin 6)
   Output - LED connected to output Y3 with PWM controlled brightness (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/
   
void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  inAnalog(X0);   // Read Input 0
  outPWM(Y0);     // Send to Output 0
  
  inAnalog(X1);   // Read Input 1
  outPWM(Y1);     // Send to Output 1

  inAnalog(X2);   // Read Input 2
  outPWM(Y2);     // Send to Output 2
  
  inAnalog(X3);   // Read Input 3
  outPWM(Y3);     // Send to Output 3
}
