#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Parallel Switch Branch and then Converge based on switch inputs
   
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)
   Output - LED connected to output Y2 (Arduino pin 6 / Tinkerkit O3)
   Output - LED connected to output Y3 (Arduino pin 9 / Tinkerkit O2)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

   Sequential Function Chart
   
   |=========|    |--------|
   |  START  |----|   Y0   |
   |=========|    |--------|
        |
       -|-- X0
        |
        |============================|
        |                            |
   |----|----|    |--------|    |----|----|    |--------|
   |  STEP1  |----|   Y1   |    |  STEP2  |----|   Y2   |
   |----|----|    |--------|    |----|----|    |--------|
        |                            |
        |============================|
        |
       -|-- X1
        |
   |----|----|    |--------| 
   |  STEP3  |----|   Y3   |
   |---------|    |--------|

   Y0 is displayed when the system is switched-on or reset
   Press X0 to simultaneously activate Steps 1 and 2, hence displaying Y1 and Y2
   Press X1 to progress to Step 3, displaying Y3
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
  set(STEP2);               // Activate Step 2
  reset(START);             // Cancel Start-up state

  in(STEP1);                // Read Step 1
  orBit(STEP2);             // OR with Step 2
  andBit(X1);               // AND with Step 4 transition input
  set(STEP3);               // Activate Step 3
  reset(STEP1);             // Cancel Step 1
  reset(STEP2);             // Cancel Step 2
  
  
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