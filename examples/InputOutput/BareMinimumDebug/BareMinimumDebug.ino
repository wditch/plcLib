#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Bare Minimum + Debug - Single bit digital input/output
                          with serial monitor enabled

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();              // Setup inputs and outputs
  Serial.begin(9600);      // Enable serial port (needed for serial IO monitor)
}

void loop() {
  in(X0);                  // Read Input 0
  out(Y0);                 // Send to Output 0

  serialMonitor("Basic");  // Enable remote I/O monitoring via the serial port
}