#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Comparator - Maximum / minimum test using fixed threshold values

   Connections:
   Analogue Input - potentiometer connected to input X0 (Arduino pin A0)
   Digital Output - 'High' LED connected to output Y0 (Arduino pin 3)
   Digital Output - 'Low' LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned int lowLimit = 307;    // Analogue lower threshold = 307
                                // (30% of 1024 = 1024 * 0.3 = 307)
                                // Lower threshold voltage = Vsupply * 0.3 
                                // (1.5 V if Vsupply = 5 V)

unsigned int highLimit = 717;   // Analogue lower threshold = 717 
                                // (70% of 1024 = 1024 * 0.7 = 717)
                                // Upper threshold voltage = Vsupply * 0.7
                                // (3.5 V if Vsupply = 5 V)

void setup() {
  setupPLC();                   // Setup inputs and outputs
}

void loop() {
  inAnalog(X0);                 // Read Analogue Input 0
  compareGT(highLimit);         // X0 > upper threshold?
  out(Y0);                      // Y0 = 1 if X0 > 717, Y0 = 0 otherwise

  inAnalog(X0);                 // Read Analogue Input 0
  compareLT(lowLimit);          // X0 < lower threshold?
  out(Y1);                      // Y1 = 1 if X0 < 307, Y1 = 0 otherwise
}
