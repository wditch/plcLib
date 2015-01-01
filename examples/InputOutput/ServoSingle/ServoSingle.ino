#include <Servo.h>
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Single Servo - Controlling the position of a servo using a potentiometer 

   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Output - servo connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Servo servo1;           // Create a servo object to control a single servo

extern int scanValue;	// Link to scanValue defined in PLC library file

void setup() {
  setupPLC();           // Setup inputs and outputs
  servo1.attach(Y0);    // Attaches Servo 1 to Output 0
}

void loop() {
  inAnalog(X0);         // Read potentiometer connected to input 0
  outServo(servo1);     // Output to Servo 1 (connected to Output 0)
}

// The outServo function is defined locally
int outServo(Servo &ServoObj) {
  ServoObj.write(map(scanValue, 0, 1023, 0, 179));
  return(scanValue);
}


