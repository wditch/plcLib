#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Shift register: Rotate data to the right 

   Connections:
   Clock Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Reset Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)
   Output - LED connected to output Y2 (Arduino pin 6 / Tinkerkit O3)
   Output - LED connected to output Y3 (Arduino pin 9 / Tinkerkit O2)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Shift shift1(0x8000);      // Create a shift register with initial value 0x8000
                           // (Leftmost 4 bits are rotated to the right)

                           //    Outputs         Y Y Y Y
                           //                    3 2 1 0
                           //
                           //      Bit           1 1 1 1
                           //   Positions        5 4 3 2
                           //                    | | | |
                           //                 -> 1 0 0 0 ->
                           //                 |           |
                           //                 |           |
                           //  X0 -> Clock    -<--<--<--<--
                           //
                           //  X1 -> Reset

unsigned long TIMER0 = 0;  // Define variable used for switch debounce

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  
  shift1.bitValue(12);     // Read input to shift register from bit 12 at RHS
  shift1.inputBit();

  in(X0);                  // Rotate Right on rising edge of input X0
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay on X0
  shift1.shiftRight();

  in(X1);                  // Reset the shift register value to zero if X1 = 1
  shift1.reset();

  shift1.bitValue(15);      // Send bit 15 value to output Y3
  out(Y3);
  
  shift1.bitValue(14);      // Send bit 14 value to output Y2
  out(Y2);
  
  shift1.bitValue(13);      // Send bit 13 value to output Y1
  out(Y1);
  
  shift1.bitValue(12);      // Send bit 12 value to output Y0
  out(Y0);
}