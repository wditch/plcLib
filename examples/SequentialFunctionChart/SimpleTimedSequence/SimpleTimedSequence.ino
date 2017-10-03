#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Simple Timed Sequence - A three step sequence with timed transitions
   
   Connections:

   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)

   Software and Documentation:
   https://github.com/wditch/plcLib


   Sequential Function Chart
   
        |=========|    |------|
        |  START  |----|  Y0  |
        |=========|    |------|
             |
            -|-- DELAY0 = 2000 (ms)
             |
        |----|----|    |------|
        |  STEP1  |----|  Y1  |
        |---------|    |------|
             |
            -|-- DELAY1 = 4000 (ms)
             |
        |----|----|    |------|
        |  STEP2  |----|  Y2  |
        |---------|    |------|


   The Start step is active when the system is switched-on or reset, displaying Y0
   Step 1 becomes active after 2 seconds, displaying Y1
   After a further 4 seconds Step 2 becomes active, displaying Y2

*/

                            // Define state names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2

                            // Define time delay variables

unsigned long DELAY0 = 0;   // Variable to hold elapsed time for Step 0
unsigned long DELAY1 = 0;   // Variable to hold elapsed time for Step 1

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
                            // Do state transitions

  in(START);                // Read Start-up state
  timerOn(DELAY0, 2000);    // 2 second delay
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Start-up state
 
  in(STEP1);                // Read Step 1
  timerOn(DELAY1, 4000);    // 4 second delay
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1

  
                            // Display current state

  in(START);
  out(Y0);                  // Send to Output 0							

  in(STEP1);
  out(Y1);                  // Send to Output 1

  in(STEP2);
  out(Y2);                  // Send to Output 2

}