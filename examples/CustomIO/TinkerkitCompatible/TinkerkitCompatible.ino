#include <TinkerKit.h>
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Tinkerkit Compatible - Use of Tinkerkit pin names and numbers
   
   (Including the Tinkerkit library allows Tinkerkit input/output pin names
    and numbers to be used - I0-I5/O0-O5 for the Arduino Uno.)

   Connections:
   Input - switch connected to input I0 (Arduino pin A0)
   Input - switch connected to input I1 (Arduino pin A1)
   Input - switch connected to input I2 (Arduino pin A2)
   Input - switch connected to input I3 (Arduino pin A3)
   Output - LED connected to output O0 (Arduino pin 11)
   Output - LED connected to output O1 (Arduino pin 10)
   Output - LED connected to output O2 (Arduino pin 9)
   Output - LED connected to output O3 (Arduino pin 6)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  in(I0);      // Read Input 0 and send to Output 0
  out(O0);

  inNot(I1);   // Read Input 1 (inverted) and send to Output 1
  out(O1);

  in(I2);      // Read Input 2 and send to Output 2 (inverted)
  outNot(O2);
  
  inNot(I3);   // Read Input 2 (inverted) and send to Output 2 (inverted)
  outNot(O3);  // (The double negative cancels out)
}
