#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Shift register: Johnson counter created by rotating data to the left 
                   with inverted leftmost bit fed back to RHS

   Connections:
   Clock Input - switch connected to input X0 (Arduino pin A0)
   Reset Input - switch connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y0 (Arduino pin 3)
   Output - LED connected to output Y1 (Arduino pin 5)
   Output - LED connected to output Y2 (Arduino pin 6)
   Output - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Shift shift1(0x0000);      // Create a shift register with initial value 0x0000
                           // (Rightmost 4 bits are rotated to the left)

                           //    Outputs         Y Y Y Y
                           //                    3 2 1 0
                           //      Bit
                           //   Positions        3 2 1 0
                           //                    | | | |
                           //                 <- 0 0 0 0 <-
                           //                 |           |
                           //               |Not|         |
                           //                 |           |
                           //  X0 -> Clock    ->-->-->-->--
                           //
                           //  X1 -> Reset

unsigned long TIMER0 = 0;  // Define variable used for switch debounce
unsigned int AUX0;         // Temporary storage for inverted feedback bit

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  
  shift1.bitValue(3);       // 'Feedback' input to shift register from bit 3 at LHS
  outNot(AUX0);             // is inverted and temporarily stored in AUX0

  in(AUX0);                 // Use inverted feedback bit as shift register input
  shift1.inputBit();

  in(X0);                  // Rotate Left on rising edge of input X0
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay on X0
  shift1.shiftLeft();

  in(X1);                  // Reset the shift register value to zero if X1 = 1
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