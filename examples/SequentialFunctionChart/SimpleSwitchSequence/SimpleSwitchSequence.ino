#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Simple Sequence - A Three step sequence with push button control
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib


   Sequential Function Chart
   
        |=========|
        |  START  |
        |=========|
             |
            -|-- X0
             |
        |----|----|    |------|
        |  STEP1  |----|  Y0  |
        |---------|    |------|
             |
            -|-- X1
             |
        |----|----|    |------|
        |  STEP2  |----|  Y1  |
        |---------|    |------|


   The Start step is active when the system is switched-on or reset
   Press X0 to activate Step 1, displaying Y0
   Next, press X1 to activate Step 2, displaying Y1
   
*/

                            // Define state names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
                            // Do state transitions

  in(START);                // Read Start-up state
  andBit(X0);               // AND with Step 1 transition input
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Start-up state
 
  in(STEP1);                // Read Step 1
  andBit(X1);               // AND with Step 2 transition input
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1

  
                            // Display current state
  
  in(STEP1);
  out(Y0);                  // Send to Output 0

  in(STEP2);
  out(Y1);                  // Send to Output 1

}