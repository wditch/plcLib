#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Millis() Rollover test

   (Sets timer to 10 seconds before millis() rollover to allow testing of 
   timer operation during rollover. Set serial monitor to 57,600 Baud and
   open monitor to display current timer value.)

   Fixed Pulse - Activates an output for a fixed period after a momentary input is applied

   Connections:
   Input - switch connected to input X0 (Arduino pin A0)
   Output with 2 s pulse - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned long TIMER0 = 0;                     // Variable to hold elapsed time for Timer 0
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
  timerPulse(TIMER0, 5000);                   // 5 second pulse
  out(Y0);                                    // Output to Output 0

  Serial.print(" Millis: ");                  // Display millis() value to view rollover
  Serial.println(millis()/1000);
  delay(10);
}