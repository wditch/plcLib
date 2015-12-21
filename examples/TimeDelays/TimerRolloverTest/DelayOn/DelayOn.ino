#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Millis() Rollover test
   
   (Sets timer to 10 seconds before millis() rollover to allow testing of 
   timer operation during rollover. Set serial monitor to 57,600 Baud and
   open monitor to display current timer value.)

   Turn-on Delay - Delays turning an output on after an input is applied

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Input - switch connected to input X1 (Arduino pin A1)
   Output with 2 s delay - LED connected to output Y0 (Arduino pin 3)
   Output with 4 s delay - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned long TIMER0 = 0;                     // Variable to hold elapsed time for Timer 0
unsigned long TIMER1 = 0;                     // Variable to hold elapsed time for Timer 1
extern volatile unsigned long timer0_millis;  // External variable used by millis() command
unsigned long timeToGo = 4294967296-10000;    // Variable to set millis() value to 10 seconds before rollover

void setup() {
  setupPLC();                                 // Setup inputs and outputs
  Serial.begin(57600);                        // Enable serial monitor (57600 Baud)
  noInterrupts ();                            // Set millis() to 10 seconds before rollover
  timer0_millis = timeToGo;
  interrupts ();
}

void loop() {
  in(X0);                                     // Read Input 0
  timerOn(TIMER0, 5000);                      // 5 second delay
  out(Y0);                                    // Output to Output 0

  in(X1);                                     // Read Input 1
  timerOn(TIMER1, 10000);                     // 10 second delay
  out(Y1);                                    // Output to Output 1
  
  
  Serial.print(" Millis: ");                  // Display millis() value to view rollover
  Serial.println(millis()/1000);
  delay(10)
}