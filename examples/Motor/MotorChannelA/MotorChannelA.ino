#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Motor Channel A - Simple Motor Control on Arduino Motor Shield Channel A

   Connections:
   Input - Speed - potentiometer connected to input X2 (Arduino pin A2)
   Input - Direction - switch connected to input X3 (Arduino pin A3)
   Output - Channel A Direction (DIRA) - Arduino pin 12
   Output - Channel A PWM (PWMA) - Arduino pin 3
   Output - Channel A Brake (BRAKEA) - Arduino pin 9

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

// Variables
unsigned int RUN = 0;  // Disable brake

void setup() {
  setupPLC();          // Setup inputs and outputs

                       // Turn off Channel A Brake
  in(RUN);             // Read RUN variable (0 = brake off)
  out(BRAKEA);         // Output to BRAKEA
}

void loop() {
                       // Control direction of motor 
  in(X3);              // Read switch connected to Input 3
  out(DIRA);           // Output to DIRA (motor direction)

                       // Read Analog Input 2 and send to Channel A PWM
  inAnalog(X2);        // Read from potentiometer connected to Analogue Input 2
  outPWM(PWMA);        // Output to PWMA (motor speed)
}


