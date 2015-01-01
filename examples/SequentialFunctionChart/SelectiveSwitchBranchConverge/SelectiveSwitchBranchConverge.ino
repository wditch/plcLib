#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Selective Switch Branch and then Converge based on switch inputs
   
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Input - switch connected to input X2 (Arduino pin A2 / Tinkerkit pin I2)
   Input - switch connected to input X3 (Arduino pin A3 / Tinkerkit pin I3)
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
        |----------------------------|
        |                            |
       -|-- X0                      -|-- X1
        |                            |
   |----|----|    |--------|    |----|----|    |--------|
   |  STEP1  |----|   Y1   |    |  STEP2  |----|   Y2   |
   |----|----|    |--------|    |----|----|    |--------|
        |                            |
       -|-- X2                      -|-- X3
        |                            |
        |----------------------------|
        |
   |----|----|    |--------| 
   |  STEP3  |----|   Y3   |
   |---------|    |--------|

   Y0 is displayed when the system is switched-on or reset
   Press X0 to activate Step 1, or X1 to activate Step 2, displaying Y1 or Y2
   Press X2 to progress from Step 1 to 3, or X3 to move from Step 2 to 3, displaying Y3

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

  in(STEP1);                // Read Step 1
  andBit(X2);               // AND with Step 3 transition input
  set(STEP3);               // Activate Step 3
  reset(STEP1);             // Cancel Step 1
  
  in(STEP2);                // Read Step 2
  andBit(X3);               // AND with Step 3 transition input
  set(STEP3);               // Activate Step 3
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