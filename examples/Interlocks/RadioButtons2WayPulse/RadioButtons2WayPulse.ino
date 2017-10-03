#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Using Set and Reset commands to create a 2-way radio button array with single-shot pulse inputs

   Note: With this design, a momentary press on an input activates a 1-shot pulse, which in turn
         triggers the corresponding latch. In the event that the original input switch is held down
         (or becomes stuck in that position due to a fault) then the next active input is able to
         override the previous input. 

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

Pulse button1, button2;         // Create a pulse objects for buttons 1 and 2

void setup() {
  setupPLC();          // Setup inputs and outputs
}

void loop() {
  in(X0);              // Read switch connected to Input 0 and
  button1.inClock();   // connect it to button 1

  in(X1);              // Read switch connected to Input 1 and
  button2.inClock();   // connect it to button 2

  button1.rising();    // Read rising edge of button 1
  set(Y0);             // Set Y0 if X0 = 1 momentarily
  reset(Y1);           // Clear Y1 if X0 = 1 momentarily

  button2.rising();    // Read rising edge of button 2
  set(Y1);             // Set Y1 if X1 = 1 momentarily
  reset(Y0);           // Clear Y0 if X1 = 1 momentarily
}