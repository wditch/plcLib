#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Shift register: Pseudo Random Number Generator based on a feedback shift register

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

Shift shift1(0xACE1);      // Create a 16 bit shift register with initial value 0xACE1

                           //                                       Y Y Y Y
                           //                            Outputs    3 2 1 0
                           //                                       | | | |
                           //      Bit      1 1 1 1 1 1
                           //   Positions   5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
                           //               | | | | | | | | | | | | | | | |
                           //               1 0 1 0 1 1 0 0 1 1 1 0 0 0 0 1 <-|
                           //               |   | |   |                       |
                           //  X0 -> Clock  |XOR| |   |                       |
                           //                 |   |   |                       |
                           //  X1 -> Reset    |XOR|   |                       |
                           //                   |     |                       |
                           //                   | XOR |                       |
                           //                      |                          |
                           //                      -->-->-->-->-->-->-->-->-->-

unsigned long TIMER0 = 0;       // Define variable used for switch debounce
unsigned int AUX0, AUX1, AUX2;  // Temporary storage variables for feedback taps

void setup() {
  setupPLC();              // Setup inputs and outputs
  Serial.begin(9600);      // Open serial connection over USB (optional)
}

void loop() {

                           // Read feedback taps
  shift1.bitValue(15);     // Read bit 15
  out(AUX0);
  
  shift1.bitValue(12);     // Read bit 12
  out(AUX1);
  
  shift1.bitValue(10);     // Read bit 10
  out(AUX2);
  
  shift1.bitValue(13);     // Calculate feedback value
  xorBit(AUX0);
  xorBit(AUX1);
  xorBit(AUX2);
  shift1.inputBit();

  in(X0);                  // Shift Left on rising edge of input X0
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

                                   // Use serial monitor to view shift register values
  Serial.println(shift1.value());  // Send value to serial port (optional)
  delay(200);                      // 0.2 second serial print delay (optional)
}