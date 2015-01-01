#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Do While - Wait for an input before starting the main scan loop

   (Note: The Do While loop always runs at least once, because the exit test is
          at the end. This contrasts with the While loop, where the test is at
          the start.

   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - potentiometer connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int myVar = 0;   // Create a user defined variable and set initial value

void setup() {
  setupPLC();             // Setup inputs and outputs
  
  do {
    myVar = in(X0);
  } while (myVar == 0);   // Repeat loop until X0 = 1, then continue
}

void loop() {
  inAnalog(X1);           // Read Analogue Input 1
  outPWM(Y0);             // Send to Output 0 as PWM waveform
}

