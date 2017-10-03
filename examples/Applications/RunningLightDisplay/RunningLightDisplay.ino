#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Running Light Display - Timed Repeating Sequence
   
   Connections:
   Output - Red LED connected to output Y0 (Arduino pin 3)
   Output - Amber LED connected to output Y1 (Arduino pin 5)
   Output - Green LED connected to output Y2 (Arduino pin 6)
   Output - Blue LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

   Sequential Function Chart
   
         |=========|    |---------------|
         |  START  |----|  -- -- -- --  |
         |=========|    |---------------|
              |
             -|-- DELAY0 = 200 (ms)
              |
|------>------|
|             |
|        |----|----|    |---------------|
|        |  STEP1  |----|  Y0 -- -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY1 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP2  |----|  Y0 Y1 -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY2 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP3  |----|  -- Y1 Y2 --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY3 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP4  |----|  -- -- Y2 Y3  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY4 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP5  |----|  -- -- -- Y3  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY5 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP6  |----|  -- -- -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY6 = 1000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP7  |----|  -- -- -- Y3  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY7 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP8  |----|  -- -- Y2 Y3  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY8 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP9  |----|  -- Y1 Y2 --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY9 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP10 |----|  Y0 Y1 -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY10 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP11 |----|  Y0 -- -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY11 = 200 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP12 |----|  -- -- -- --  |
|        |---------|    |---------------|
|             |
|            -|-- DELAY12 = 1000 (ms)
|             |
|------<------|

The system begins in the Start-up state, proceeding to Step 1 after 0.2 seconds
Steps 1 - 12 are executed in a repeating sequence with delay controlled transitions
Outputs Y0 - Y3 are displayed according to the following table

  Step (Variable)    Y0    Y1    Y2    Y3    Duration (Variable)
   0    (START)      -     -     -     -      200 ms   (DELAY0)
   1    (STEP1)      x     -     -     -      200 ms   (DELAY1)
   2    (STEP2)      x     x     -     -      200 ms   (DELAY2)
   3    (STEP3)      -     x     x     -      200 ms   (DELAY3)
   4    (STEP4)      -     -     x     x      200 ms   (DELAY4)
   5    (STEP5)      -     -     -     x      200 ms   (DELAY5)
   6    (STEP6)      -     -     -     -      1000 ms  (DELAY6)
   7    (STEP7)      -     -     -     x      200 ms   (DELAY7)
   8    (STEP8)      -     -     x     x      200 ms   (DELAY8)
   9    (STEP9)      -     x     x     -      200 ms   (DELAY9)
   10   (STEP10)     x     x     -     -      200 ms   (DELAY10)
   11   (STEP11)     x     -     -     -      200 ms   (DELAY11)
   12   (STEP12)     -     -     -     -      1000 ms  (DELAY12)

*/
                            // Define step names for Sequential Function Chart program

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2
unsigned int STEP3 = 0;     // Step 3
unsigned int STEP4 = 0;     // Step 4
unsigned int STEP5 = 0;     // Step 5
unsigned int STEP6 = 0;     // Step 6
unsigned int STEP7 = 0;     // Step 7
unsigned int STEP8 = 0;     // Step 8
unsigned int STEP9 = 0;     // Step 9
unsigned int STEP10 = 0;    // Step 10
unsigned int STEP11 = 0;    // Step 11
unsigned int STEP12 = 0;    // Step 12


                            // Define time delay variables

unsigned long DELAY0 = 0;   // Variable to hold elapsed time for Step 0
unsigned long DELAY1 = 0;   // Variable to hold elapsed time for Step 1
unsigned long DELAY2 = 0;   // Variable to hold elapsed time for Step 2
unsigned long DELAY3 = 0;   // Variable to hold elapsed time for Step 3
unsigned long DELAY4 = 0;   // Variable to hold elapsed time for Step 4
unsigned long DELAY5 = 0;   // Variable to hold elapsed time for Step 5
unsigned long DELAY6 = 0;   // Variable to hold elapsed time for Step 6
unsigned long DELAY7 = 0;   // Variable to hold elapsed time for Step 7
unsigned long DELAY8 = 0;   // Variable to hold elapsed time for Step 8
unsigned long DELAY9 = 0;   // Variable to hold elapsed time for Step 9
unsigned long DELAY10 = 0;   // Variable to hold elapsed time for Step 10
unsigned long DELAY11 = 0;   // Variable to hold elapsed time for Step 11
unsigned long DELAY12 = 0;   // Variable to hold elapsed time for Step 12

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
                            // Do timed step transitions

  in(START);                // Read startup step - Step 0
  timerOn(DELAY0, 200);     // 0.2 second delay
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Step 0
  
  in(STEP1);                // Read Step 1
  timerOn(DELAY1, 200);     // 0.2 second delay
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1
 
  in(STEP2);                // Read Step 2
  timerOn(DELAY2, 200);     // 0.2 second delay
  set(STEP3);               // Activate Step 3
  reset(STEP2);             // Cancel Step 2
  
  in(STEP3);                // Read Step 3
  timerOn(DELAY3, 200);     // 0.2 second delay
  set(STEP4);               // Activate Step 4
  reset(STEP3);             // Cancel Step 3
  
  in(STEP4);                // Read Step 4
  timerOn(DELAY4, 200);     // 0.2 second delay
  set(STEP5);               // Activate Step 5
  reset(STEP4);             // Cancel Step 4
  
  in(STEP5);                // Read Step 5
  timerOn(DELAY5, 200);     // 0.2 second delay
  set(STEP6);               // Activate Step 6
  reset(STEP5);             // Cancel Step 5
  
  in(STEP6);                // Read Step 6
  timerOn(DELAY6, 1000);    // 1 second delay
  set(STEP7);               // Activate Step 7
  reset(STEP6);             // Cancel Step 6
  
  in(STEP7);                // Read Step 7
  timerOn(DELAY7, 200);     // 0.2 second delay
  set(STEP8);               // Activate Step 8
  reset(STEP7);             // Cancel Step 7
  
  in(STEP8);                // Read Step 8
  timerOn(DELAY8, 200);     // 0.2 second delay
  set(STEP9);               // Activate Step 9
  reset(STEP8);             // Cancel Step 8
  
  in(STEP9);                // Read Step 9
  timerOn(DELAY9, 200);     // 0.2 second delay
  set(STEP10);              // Activate Step 10
  reset(STEP9);             // Cancel Step 9
  
  in(STEP10);               // Read Step 10
  timerOn(DELAY10, 200);    // 0.2 second delay
  set(STEP11);              // Activate Step 11
  reset(STEP10);            // Cancel Step 10
  
  in(STEP11);               // Read Step 11
  timerOn(DELAY11, 200);    // 0.2 second delay
  set(STEP12);              // Activate Step 12
  reset(STEP11);            // Cancel Step 11
  
  in(STEP12);               // Read Step 12
  timerOn(DELAY12, 1000);   // 1 second delay
  set(STEP1);               // Activate Step 1
  reset(STEP12);            // Cancel Step 12


                            // Display outputs according to table
							
                            // Display Y0 if step = 1, 2, 10 or 11
  in(STEP1);                // Read Step 1
  orBit(STEP2);             // OR with Step 2
  orBit(STEP10);            // OR with Step 10
  orBit(STEP11);            // OR with Step 11
  out(Y0);                  // Send to Output 0 (Red)
  
                            // Display Y1 if step = 2, 3, 9 or 10
  in(STEP2);                // Read Step 2
  orBit(STEP3);             // OR with Step 3
  orBit(STEP9);             // OR with Step 9
  orBit(STEP10);            // OR with Step 10
  out(Y1);                  // Send to Output 1 (Amber)

                            // Display Y2 if step = 3, 4, 8 or 9
  in(STEP3);                // Read Step 3
  orBit(STEP4);             // OR with Step 4
  orBit(STEP8);             // OR with Step 8
  orBit(STEP9);             // OR with Step 9
  out(Y2);                  // Send to Output 2 (Green)
  
                            // Display Y3 if step = 4, 5, 7 or 8
  in(STEP4);                // Read Step 4
  orBit(STEP5);             // OR with Step 5
  orBit(STEP7);             // OR with Step 7
  orBit(STEP8);             // OR with Step 8
  out(Y3);                  // Send to Output 3 (Blue)

}