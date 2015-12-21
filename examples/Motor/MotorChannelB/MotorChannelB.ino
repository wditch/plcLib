#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Motor Channel B - Simple Motor Control on Arduino Motor Shield Channel B

   Connections:
   Input - Speed - potentiometer connected to input X2 (Arduino pin A2)
   Input - Direction - switch connected to input X3 (Arduino pin A3)
   Output - Channel B Direction (DIRB) - Arduino pin 13
   Output - Channel B PWM (PWMB) - Arduino pin 11
   Output - Channel B Brake (BRAKEB) - Arduino pin 8

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

// Variables:
unsigned int RUN = 0;  // Disable brake

void setup() {
  setupPLC();          // Setup inputs and outputs

                       // Turn off Channel B Brake
  in(RUN);             // Read RUN variable (0 = brake off)
  out(BRAKEB);         // Output to BRAKEB
}

void loop() {
                       // Control direction of motor
  in(X3);              // Read switch connected to Input 3
  out(DIRB);           // Output to DIRB (motor direction)

                       // Read Analog Input 2 and send to Channel B PWM
  inAnalog(X2);        // Read from potentiometer connected to Analogue Input 2
  outPWM(PWMB);        // Output to PWMB (motor speed)
}


