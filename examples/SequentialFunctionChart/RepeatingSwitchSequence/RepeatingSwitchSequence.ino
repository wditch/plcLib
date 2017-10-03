#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Repeating Sequence - A four step repeating sequence with push button control
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Input - switch connected to input X2 (Arduino pin A2)
   Input - switch connected to input X3 (Arduino pin A3)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib


   Sequential Function Chart
   
         |=========|    |---------------|
         |  START  |----|  Y0 -- -- --  |
         |=========|    |---------------|
              |
             -|-- X0
              |
|------>------|
|             |
|        |----|----|    |---------------|
|        |  STEP1  |----|  -- Y1 -- --  |
|        |---------|    |---------------|
|             |
|            -|-- X1
|             |
|        |----|----|    |---------------|
|        |  STEP2  |----|  -- -- Y2 --  |
|        |---------|    |---------------|
|             |
|            -|-- X2
|             |
|        |----|----|    |---------------|
|        |  STEP3  |----|  -- -- -- Y3  |
|        |---------|    |---------------|
|             |
|            -|-- X3
|             |
|------<------|

   Y0 is displayed when the system is switched-on or reset
   Press X0 to activate Step 1, displaying Y1
   Next, press X1 to activate Step 2, displaying Y2
   Next, press X2 to activate Step 3, displaying Y3
   Next, press X3 to move back to Step 1
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
 
  in(STEP1);                // Read Step 1
  andBit(X1);               // AND with Step 2 transition input
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1

  in(STEP2);                // Read Step 2
  andBit(X2);               // AND with Step 3 transition input
  set(STEP3);               // Activate Step 3
  reset(STEP2);             // Cancel Step 2
  
  in(STEP3);                // Read Step 3
  andBit(X3);               // AND with Step 1 transition input
  set(STEP1);               // Go back to Step 1
  reset(STEP3);             // Cancel Step 3
  
  
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