#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Average - Create a custom function to calculate the mean of two analogue inputs

   Connections:
   Input - Potentiometer connected to analogue input X0 (Arduino pin A0)
   Input - Potentiometer connected to analogue input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int reading1;
unsigned int reading2;
extern int scanValue;	// Link to scanValue defined in PLC library file

void setup() {
  setupPLC();                               // Setup inputs and outputs
}

void loop() {
  reading1 = inAnalog(X0);                  // Read analogue Input 0
  reading2 = inAnalog(X1);                  // Read analogue Input 1
  scanValue = average(reading1, reading2);  // Set scanValue to average reading
  outPWM(Y0);                               // Send to Output 0
}

                                            // User defined function to calculate
                                            // the average of two values
											
unsigned int average(unsigned int value1, unsigned int value2) {
  int result;
  result = (value1 + value2) / 2;
  return result;
}