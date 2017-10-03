#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Comparator - Greater than test between an input and a fixed threshold

   Connections:
   Analogue Input - potentiometer connected to input X0 (Arduino pin A0)
   Digital Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned int threshold = 500;   // Analogue threshold = 500
   
void setup() {
  setupPLC();                   // Setup inputs and outputs
}

void loop() {
  inAnalog(X0);                 // Read Analogue Input 0
  compareGT(threshold);         // X0 > 500?
  out(Y0);                      // Y0 = 1 if X0 > 500, Y0 = 0 otherwise

}
