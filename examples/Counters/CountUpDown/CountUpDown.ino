#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Up-down Counter - Counts up or down in the range 0-10

   Connections:
   Count up input - switch connected to input X0 (Arduino pin A0 / Tinkerkit pin I0)
   Count down input - switch connected to input X1 (Arduino pin A1 / Tinkerkit pin I1)
   Clear input - switch connected to input X2 (Arduino pin A2 / Tinkerkit pin I2)
   Preset input - switch connected to input X3 (Arduino pin A3 / Tinkerkit pin I3)
   Lower Q output - LED connected to output Y0 (Arduino pin 3 / Tinkerkit O5)
   Upper Q output - LED connected to output Y1 (Arduino pin 5 / Tinkerkit O4)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Counter ctr(10);           // Counts up or down in range 0-10, starting at zero
unsigned long TIMER0 = 0;  // Define variable used to hold timer 0 elapsed time
unsigned long TIMER1 = 0;  // Define variable used to hold timer 1 elapsed time

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay
  ctr.countUp();           // Count up

  in(X1);                  // Read Input 1
  timerOn(TIMER1, 10);     // 10 ms switch debounce delay
  ctr.countDown();         // Count down

  in(X2);                  // Read input X1
  ctr.clear();             // Clear counter (counter at lower limit)
  
  in(X3);                  // Read input X2
  ctr.preset();            // Preset counter (counter at upper limit)

  ctr.lowerQ();            // Display Count Down output on Y0
  out(Y0);
  
  ctr.upperQ();            // Display Count Up output on Y1
  out(Y1);
}