#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Simple Alarm - A 3-input alarm circuit with a latched output and manual Reset input

   Connections:
   Input - Sensor 0 - switch connected to input X0 (Arduino pin A0)
   Input - Sensor 1 - switch connected to input X1 (Arduino pin A1)
   Input - Sensor 3 - switch connected to input X2 (Arduino pin A2)
   Input - Reset Alarm - switch connected to input X3 (Arduino pin A3)
   Output - Alarm Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

void setup() {
  setupPLC();       // Setup inputs and outputs
}

void loop() {
  in(X0);           // Read Sensor 0 (Input 0)
  orBit(X1);        // OR with Sensor 1 (Input 1)
  orBit(X2);        // OR with Sensor 2 (Input 2)

                    // Sensor result is used as Set input to latch
  latch(Y0, X3);    // Latch command, Q = Output 0, Reset = Input 3
}
