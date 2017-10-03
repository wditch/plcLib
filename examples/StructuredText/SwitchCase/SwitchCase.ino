#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Switch Case - Read an analogue sensor on X3 and use it to route data from one of three
                 possible digital inputs (X0-X2) to a single output (Y0)
   

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - potentiometer connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

unsigned int sensorReading;        // User variable to hold sensor reading from Input 0
unsigned int minReading = 9;       // Set this to the minimum reading from your potentiometer / sensor
unsigned int maxReading = 900;     // Set this to the maximum reading from your potentiometer / sensor
unsigned int mappedRange;          // User variable to hold mapped sensor value (0-3)


void setup() {
  setupPLC();                      // Setup inputs and outputs
}

void loop() {
  sensorReading = inAnalog(X3);     // Read analogue Input 3, storing result in user variable
  mappedRange = map(sensorReading, minReading, maxReading, 0, 2);  // Map sensor reading into 3 bands
  switch (mappedRange) {
  case 0:                           // Connect X0 -> Y0 if analogue sensor is in low third of range
    in(X0);
	out(Y0);
    break;
  case 1:                           // Connect X1 -> Y0 if analogue sensor is in middle third of range
    in(X1);
	out(Y0);
    break;
  case 2:                           // Connect X2 -> Y0 if analogue sensor is in upper third of range
    in(X2);
	out(Y0);
    break;
  }
}

