#include <Servo.h>
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Single Servo + Debug - Control the position of a servo using a potentiometer 
                          with serial monitor enabled

   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0)
   Output - servo connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

Servo servo1;           // Create a servo object to control a single servo

extern int scanValue;	// Link to scanValue defined in PLC library file

void setup() {
  setupPLC();           // Setup inputs and outputs
  Serial.begin(9600);   // Enable the serial port (needed for Serial Monitor)
  servo1.attach(Y0);    // Attach Servo 1 to Output 0
}

void loop() {
  inAnalog(X0);         // Read potentiometer connected to input 0
  outServo(servo1);     // Output to Servo 1 (connected to Output 0)
  
                                            // Update servo1 (Y0) pin output status for serial monitor
  pinStatusUpdate(Y0, 1, scanValue);        // pin number = Y0, type = 1 (servo output), command result = scanValue

  serialMonitor("Basic");                   // Enable remote debugging via the serial port
}

// The outServo function is defined locally
int outServo(Servo &ServoObj) {
  ServoObj.write(map(scanValue, 0, 1023, 0, 179));
  return(scanValue);
}


