#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   On/Off Control of an Output based on rising and falling edge transitions
   
   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/


   Sequential Function Chart
   
        |=========|
        |  START  |
        |=========|
             |
            -|-- X0 Rising
             |
   |---->----|
   |         |
   |    |----|----|    |------|
   |    |  STEP1A |----|  Y0  |
   |    |---------|    |------|
   |         |
   ^        -|-- X0 Falling
   |         |
   |    |----|----|    |------|
   |    |  STEP1B |----|  Y0  |
   |    |---------|    |------|
   |         |
   |        -|-- X0 Rising
   |         |
   |    |----|----|    |------|
   |    |  STEP2A |----|      |
   |    |---------|    |------|
   ^         |
   |        -|-- X0 Falling
   |         |
   |    |----|----|    |------|
   ^    |  STEP2B |----|      |
   |    |---------|    |------|
   |         |
   |        -|-- X0 Rising
   |         |
   |----<----|

   The Start step is active when the system is switched-on or reset
   Press and release X0 to move through the sequence flashing output Y0 on/off
   
*/

                            // Define state names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1A = 0;    // Step 1A
unsigned int STEP1B = 0;    // Step 1B
unsigned int STEP2A = 0;    // Step 2A
unsigned int STEP2B = 0;    // Step 2B

Pulse pulse1;               // Create a pulse object called 'pulse1'

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
  
  in(X0);                   // Read switch connected to Input 0 and
  pulse1.inClock();         // connect it to the clock input
  
                            // Do state transitions

  pulse1.rising();          // Read rising edge of X0
  andBit(START);            // AND with current state
  set(STEP1A);              // Activate Step 1A
  reset(START);             // Cancel Start-up state
 
  pulse1.falling();         // Read falling edge of X0
  andBit(STEP1A);           // AND with current state
  set(STEP1B);              // Activate Step 1B
  reset(STEP1A);            // Cancel Step 1A

  pulse1.rising();          // Read rising edge of X0
  andBit(STEP1B);           // AND with current state
  set(STEP2A);              // Activate Step 2A
  reset(STEP1B);            // Cancel Step 1B
  
  pulse1.falling();         // Read falling edge of X0
  andBit(STEP2A);           // AND with current state
  set(STEP2B);              // Activate Step 2B
  reset(STEP2A);            // Cancel Step 2A

  pulse1.rising();          // Read rising edge of X0
  andBit(STEP2B);           // AND with current state
  set(STEP1A);              // Activate Step 1A
  reset(STEP2B);            // Cancel Step 1B
  

                            // Display current state
  
  in(STEP1A);               // If STEP1A OR STEP1B is active
  orBit(STEP1B);            
  out(Y0);                  // Enable Output 0

  in(STEP2A);               // If STEP2A OR STEP2B is active
  orBit(STEP2B);
  outNot(Y0);               // Disable Output 0

}
