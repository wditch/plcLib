#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Selective Switch Branch - Move to one of three states based on switch inputs
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

   Sequential Function Chart
   
   |=========|    |--------|
   |  START  |----|   Y0   |
   |=========|    |--------|
        |
        |----------------------------|----------------------------|
        |                            |                            |
       -|-- X0                      -|-- X1                      -|-- X2
        |                            |                            |
   |----|----|    |--------|    |----|----|    |--------|    |----|----|    |--------|
   |  STEP1  |----|   Y1   |    |  STEP2  |----|   Y2   |    |  STEP3  |----|   Y3   |
   |---------|    |--------|    |---------|    |--------|    |---------|    |--------|
   
   Y0 is displayed when the system is switched-on or reset
   Press X0 to activate Step 1, X1 to activate Step 2, or X2 to activate Step 3
   Y1, Y2 or Y3 will be displayed depending on whether Step 1, 2, or 3 is active

*/

                            // Define state names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2
unsigned int STEP3 = 0;     // Step 3

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
                            // Do state transitions

  in(START);                // Read Start-up state
  andBit(X0);               // AND with Step 1 transition input
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Start-up state

  in(START);                // Read Start-up state
  andBit(X1);               // AND with Step 2 transition input
  set(STEP2);               // Activate Step 2
  reset(START);             // Cancel Start-up state

  in(START);                // Read Start-up state
  andBit(X2);               // AND with Step 3 transition input
  set(STEP3);               // Activate Step 3
  reset(START);             // Cancel Start-up state


                            // Display current state

  in(START);
  out(Y0);                  // Send to Output 0
  
  in(STEP1);
  out(Y1);                  // Send to Output 1

  in(STEP2);
  out(Y2);                  // Send to Output 2
  
  in(STEP3);
  out(Y3);                  // Send to Output 3

}