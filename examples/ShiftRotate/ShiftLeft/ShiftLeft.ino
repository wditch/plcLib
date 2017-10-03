#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Shift register: Shift data to the left 

   Connections:
   Serial Input - switch connected to input X0 (Arduino pin A0)
   Clock Input - switch connected to input X1 (Arduino pin A1)
   Reset Input - switch connected to input X2 (Arduino pin A2)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

Shift shift1(0x1111);      // Create a 16 bit shift register with initial value 0x1111

                           //      Bit      1 1 1 1    1 1
                           //   Positions   5 4 3 2    1 0 9 8    7 6 5 4    3 2 1 0
                           //               | | | |    | | | |    | | | |    | | | |
                           //            <- 0 0 0 1 <- 0 0 0 1 <- 0 0 0 1 <- 0 0 0 1 <- X0
                           //                                                | | | |
                           //  X1 -> Clock                                   | | | |
                           //                                                | | | |
                           //  X2 -> Reset                                   | | | |
                           //
                           //                                                Y Y Y Y
                           //                                     Outputs    3 2 1 0

unsigned long TIMER0 = 0;  // Define variable used for switch debounce

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  
  in(X0);                  // Read input to shift register from X0
  shift1.inputBit();

  in(X1);                  // Shift Left on rising edge of input X1
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay on X1
  shift1.shiftLeft();

  in(X2);                  // Reset the shift register value to zero if X2 = 1
  shift1.reset();

  shift1.bitValue(3);      // Send bit 3 value to output Y3
  out(Y3);
  
  shift1.bitValue(2);      // Send bit 2 value to output Y2
  out(Y2);
  
  shift1.bitValue(1);      // Send bit 1 value to output Y1
  out(Y1);
  
  shift1.bitValue(0);      // Send bit 0 value to output Y0
  out(Y0);
}