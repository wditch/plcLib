#include <Servo.h>
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Dual Servo + Debug - Analogue control of a pair of hobby servos
                        with serial monitor enabled
   
   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0)
   Input - potentiometter connected to input X1 (Arduino pin A1)
   Output - servo connected to output Y0 (Arduino pin 3)
   Output - servo connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

Servo servo1;           // Create servo objects to control 2 servos
Servo servo2;

extern int scanValue;	// Link to scanValue defined in PLC library file

void setup() {
  setupPLC();           // Setup inputs and outputs
  Serial.begin(9600);   // Enable the serial port (needed for Serial Monitor)
  servo1.attach(Y0);    // Attach Servo 1 to Output 0
  servo2.attach(Y1);    // Attach Servo 2 to Output 1
}

void loop() {
  inAnalog(X0);         // Read potentiometer connected to input 0
  outServo(servo1);     // Output to Servo 1 (connected to Output 0)

                                            // Update servo1 (Y0) pin output status for serial monitor
  pinStatusUpdate(Y0, 1, scanValue);        // pin number = Y0, type = 1 (servo output), command result = scanValue

  inAnalog(X1);         // Read potentiometer connected to input 1
  outServo(servo2);     // Output to Servo 1 (connected to Output 1)

                                            // Update servo2 (Y1) pin output status for serial monitor
  pinStatusUpdate(Y1, 1, scanValue);        // pin number = Y1, type = 1 (servo output), command result = scanValue

  serialMonitor("Basic");                   // Enable remote debugging via the serial port
}

// The outServo function is defined locally
int outServo(Servo &ServoObj) {
  ServoObj.write(map(scanValue, 0, 1023, 0, 179)); 
  return(scanValue);
}


