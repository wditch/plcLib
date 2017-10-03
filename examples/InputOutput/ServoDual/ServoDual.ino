#include <Servo.h>
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Dual Servo - Analogue control of a pair of hobby servos

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
  servo1.attach(Y0);    // Attach Servo 1 to Output 0
  servo2.attach(Y1);    // Attach Servo 2 to Output 1
}

void loop() {
  inAnalog(X0);         // Read potentiometer connected to input 0
  outServo(servo1);     // Output to Servo 1 (connected to Output 0)

  inAnalog(X1);         // Read potentiometer connected to input 1
  outServo(servo2);     // Output to Servo 1 (connected to Output 1)
}

// The outServo function is defined locally
int outServo(Servo &ServoObj) {
  ServoObj.write(map(scanValue, 0, 1023, 0, 179)); 
  return(scanValue);
}


