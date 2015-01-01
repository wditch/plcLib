#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Shift register: Shift data to the right using two cascaded shift registers

   Connections:
   Serial Input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Clock Input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Reset Input - switch connected to input X2 (Arduino pin A2 / Tinkerkit pin I2)
   Output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)
   Output - LED connected to output Y2 (Arduino pin 6 / Tinkerkit O3)
   Output - LED connected to output Y3 (Arduino pin 9 / Tinkerkit O2)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Shift shift1(0xF0F0);      // Create first 16 bit shift register with initial value 0xF0F0

                    //               Bit      1 1 1 1    1 1
                    //            Positions   5 4 3 2    1 0 9 8    7 6 5 4    3 2 1 0
                    //                        | | | |    | | | |    | | | |    | | | |
                    //         X0 -> -> -> -> 1 1 1 1 -> 0 0 0 0 -> 1 1 1 1 -> 0 0 0 0 ->
                    //
                    //         X1 -> Clock      
                    //
                    //         X2 -> Reset

Shift shift2(0xAAAA);      // Create second 16 bit shift register with initial value 0xAAAA

                    //               Bit      1 1 1 1    1 1
                    //            Positions   5 4 3 2    1 0 9 8    7 6 5 4    3 2 1 0
                    //                        | | | |    | | | |    | | | |    | | | |
                    //  Shift1.bitValue(0) -> 1 0 1 0 -> 1 0 1 0 -> 1 0 1 0 -> 1 0 1 0 ->
                    //                                                         | | | |
                    //         X1 -> Clock                                     | | | |      
                    //                                                         | | | |
                    //         X2 -> Reset                                     | | | |
                    //
                    //                                                         Y Y Y Y
                    //                                              Outputs    3 2 1 0

unsigned long TIMER0 = 0;  // Define variable used for switch debounce

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  
  in(X0);                  // Read input to shift register 1 from X0
  shift1.inputBit();
  
  shift1.bitValue(0);      // Read input to shift register 2 from
  shift2.inputBit();       // rightmost bit of shift register 1

  in(X1);                  // Shift Right on rising edge of input X1
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay on X1
  shift1.shiftRight();
  shift2.shiftRight();

  in(X2);                  // Reset both shift register values to zero if X2 = 1
  shift1.reset();
  shift2.reset();

  shift2.bitValue(3);      // Send bit 3 value of shift register 2 to output Y3
  out(Y3);
  
  shift2.bitValue(2);      // Send bit 2 value of shift register 2 to output Y2
  out(Y2);
  
  shift2.bitValue(1);      // Send bit 1 value of shift register 2 to output Y1
  out(Y1);
  
  shift2.bitValue(0);      // Send bit 0 value of shift register 2 to output Y0
  out(Y0);
}