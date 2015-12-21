#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Alarm with Armed Status LED - 3 input alarm controller with flashing Armed LED

   Connections:
   Input - Sensor 0 - switch connected to input X0 (Arduino pin A0)
   Input - Sensor 1 - switch connected to input X1 (Arduino pin A1)
   Input - Sensor 3 - switch connected to input X2 (Arduino pin A2)
   Input - Reset Alarm - switch connected to input X3 (Arduino pin A3)
   Output - Alarm Output - LED connected to output Y0 (Arduino pin 3)
   Output - Armed Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

// Timer Variables
unsigned long AUX0 = 0;     // Pulse low timer variable
unsigned long AUX1 = 0;     // Pulse high timer variable

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
  
  in(X0);                              // Read Sensor 0
  orBit(X1);                           // OR with Sensor 1
  orBit(X2);                           // OR with Sensor 2

                                       // Set input to latch taken from sensors
  latch(Y0, X3);                       // Latch command, Q = Output 0, Reset = Input 3

  inNot (X3);                          // Enable input (0 = enable)
  timerCycle(AUX0, 1900, AUX1, 100);   // Repeating pulse 1.9 s low, 0.1 s high.
  andNotBit(Y0);                       // Disable armed pulse if alarm is triggered
  out(Y1);                             // Armed pulse on output Y0
}
