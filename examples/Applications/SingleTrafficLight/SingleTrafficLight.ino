#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   UK Traffic Lights - Timed Repeating Sequence
   
   Connections:
   Output - Red LED connected to output Y0 (Arduino pin 3)
   Output - Amber LED connected to output Y1 (Arduino pin 5)
   Output - Green LED connected to output Y2 (Arduino pin 6)
   Output - Blue LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib



   Sequential Function Chart
   
         |=========|    |---------------|
         |  START  |----|  -- -- -- Y3  | (Blue)
         |=========|    |---------------|
              |
             -|-- DELAY0 = 2000 (ms)
              |
|------>------|
|             |
|        |----|----|    |---------------|
|        |  STEP1  |----|  Y0 -- -- --  | (Red)
|        |---------|    |---------------|
|             |
|            -|-- DELAY1 = 2000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP2  |----|  Y0 Y1 -- --  | (Red + Amber)
|        |---------|    |---------------|
|             |
|            -|-- DELAY2 = 2000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP3  |----|  -- -- Y2 --  | (Green)
|        |---------|    |---------------|
|             |
|            -|-- DELAY3 = 5000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP4  |----|  -- Y1 -- --  | (Amber)
|        |---------|    |---------------|
|             |
|            -|-- DELAY4 = 2000 (ms)
|             |
|------<------|

The system begins in the start-up state, proceeding to Red after 2 seconds
Red is displayed for 2 seconds
Red and Amber are displayed for 2 seconds
Green is displayed for 5 seconds
Amber is displayed for 2 seconds , after which operation resumes at the Red step

  Step (Variable)    Red (Y0) Amber (Y1) Green (Y2)  Blue (Y3)    Duration (Variable)
    0   (START)       -         -          -           X            2000 ms  (DELAY0)
    1   (STEP1)       X         -          -           -            2000 ms  (DELAY1)
    2   (STEP2)       X         X          -           -            2000 ms  (DELAY2)
    3   (STEP3)       -         -          X           -            5000 ms  (DELAY3)
    4   (STEP4)       -         X          -           -            2000 ms  (DELAY4)
    1
    2    etc.

*/
                            // Define step names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2
unsigned int STEP3 = 0;     // Step 3
unsigned int STEP4 = 0;     // Step 4

                            // Define time delay variables

unsigned long DELAY0 = 0;   // Variable to hold elapsed time for Step 0
unsigned long DELAY1 = 0;   // Variable to hold elapsed time for Step 1
unsigned long DELAY2 = 0;   // Variable to hold elapsed time for Step 2
unsigned long DELAY3 = 0;   // Variable to hold elapsed time for Step 3
unsigned long DELAY4 = 0;   // Variable to hold elapsed time for Step 4

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
                            // Do timed step transitions

  in(START);                // Read start-up step
  timerOn(DELAY0, 2000);    // 2 second delay
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Step 0
  
  in(STEP1);                // Read Step 1
  timerOn(DELAY1, 2000);    // 2 second delay
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1
 
  in(STEP2);                // Read Step 2
  timerOn(DELAY2, 2000);    // 2 second delay
  set(STEP3);               // Activate Step 3
  reset(STEP2);             // Cancel Step 2
  
  in(STEP3);                // Read Step 3
  timerOn(DELAY3, 5000);    // 5 second delay
  set(STEP4);               // Activate Step 4
  reset(STEP3);             // Cancel Step 3
  
  in(STEP4);                // Read Step 4
  timerOn(DELAY4, 2000);    // 2 second delay
  set(STEP1);               // Activate Step 1 (again)
  reset(STEP4);             // Cancel Step 4
  
  
                            // Display outputs according to table
   
                            // Step  Red  Amber Green  Blue
                            //   0     -     -     -     x
                            //   1     x     -     -     -
                            //   2     x     x     -     -
                            //   3     -     -     x     -
                            //   4     -     x     -     -
  
                            // Display Blue if step = 0
  in(START);                // Read Step 0
  out(Y3);                  // Send to Output 3 (Blue)
  
                            // Display Red if step = 1 OR 2
  in(STEP1);                // Read Step 1
  orBit(STEP2);             // OR with Step 2
  out(Y0);                  // Send to Output 0 (Red)
  
                            // Display Amber if step = 2 OR 4
  in(STEP2);                // Read Step 2
  orBit(STEP4);             // OR with Step 4
  out(Y1);                  // Send to Output 1 (Amber)

                            // Display Green if step = 3
  in(STEP3);                // Read Step 3
  out(Y2);                  // Send to Output 2 (Green)
  
}