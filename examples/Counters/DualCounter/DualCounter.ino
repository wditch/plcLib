#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Down Counter - Counts 5 pulses on Input 0 with switch debounce

   Connections:
   Count up input for counter 1 - switch connected to input X0 (Arduino pin A0)
   Count down input for counter 2 - switch connected to input X1 (Arduino pin A1)
   Clear input for counters 1 and 2 - switch connected to input X2 (Arduino pin A2)
   Preset input for counters 1 and 2 - switch connected to input X3 (Arduino pin A3)
   Lower Q output for counter 1 - LED connected to output Y0 (Arduino pin 3)
   Upper Q output for counter 1 - LED connected to output Y1 (Arduino pin 5)
   Lower Q output for counter 2 - LED connected to output Y2 (Arduino pin 6)
   Upper Q output for counter 2 - LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

Counter ctr1(5, 1);        // Counts down, starting at 5 down to zero
Counter ctr2(3);           // Counts up (by default) from 0 to 3
unsigned long TIMER0 = 0;  // Define variable used to hold timer 0 elapsed time
unsigned long TIMER1 = 0;  // Define variable used to hold timer 1 elapsed time

void setup() {
  setupPLC();              // Setup inputs and outputs
}

void loop() {
  in(X0);                  // Read Input 0
  timerOn(TIMER0, 10);     // 10 ms switch debounce delay
  ctr1.countDown();        // Count down on counter 1

  in(X1);                  // Read Input 1
  timerOn(TIMER1, 10);     // 10 ms switch debounce delay
  ctr2.countUp();          // Count up on counter 2

  in(X2);                  // Read input X1
  ctr1.clear();            // Clear counter 1 (counter at lower limit)
  ctr2.clear();            // Clear counter 2 (counter at lower limit)
  
  in(X3);                  // Read input X2
  ctr1.preset();           // Preset counter 1 (counter at upper limit)
  ctr2.preset();           // Preset counter 2 (counter at upper limit)

  ctr1.lowerQ();            // Display counter 1 lower Q output on Y0
  out(Y0);
  
  ctr1.upperQ();            // Display counter 1 upper Q output on Y1
  out(Y1);
  
  ctr2.lowerQ();            // Display counter 2 lower Q output on Y2
  out(Y2);
  
  ctr2.upperQ();            // Display counter 2 upper Q output on Y3
  out(Y3);
}