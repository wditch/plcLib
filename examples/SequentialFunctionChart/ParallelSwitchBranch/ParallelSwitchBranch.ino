#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Parallel Switch Branch - Simultaneously activate parallel branches when a switch is pressed
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
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
       -|-- X0
        |
        |============================|============================|
        |                            |                            |
   |----|----|    |--------|    |----|----|    |--------|    |----|----|    |--------|
   |  STEP1  |----|   Y1   |    |  STEP2  |----|   Y2   |    |  STEP3  |----|   Y3   |
   |---------|    |--------|    |---------|    |--------|    |---------|    |--------|
   
   Y0 is displayed when the system is switched-on or reset
   Press X0 to simultaneously activate Steps 1, 2 and 3, hence displaying Y1, Y2 and Y3
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
