#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Comparator - Greater than test between two input pins

   Connections:
   Analogue Input - potentiometer connected to input X0 (Arduino pin A0)
   Analogue Input - potentiometer connected to input X1 (Arduino pin A1)
   Digital Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/
   
void setup() {
  setupPLC();        // Setup inputs and outputs
}

void loop() {
  inAnalog(X0);      // Read Analogue Input 0
  compareGT(X1);     // X0 > X1 ?
  out(Y0);           // Y0 = 1 if X0 > X1, Y0 = 0 otherwise

}
