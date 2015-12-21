#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Millis() Rollover test

   (Sets timer to 10 seconds before millis() rollover to allow testing of 
   timer operation during rollover. Set serial monitor to 57,600 Baud and
   open monitor to display current timer value.)
   
   Pulsed Output - Creating a repeating pulse using the timerCycle command

   Connections:
   Input - Enable input connected to input X0 (Arduino pin A0)
   Output - Pulse Waveform on LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

// Variables:
unsigned long AUX0 = 0;                       // Pulse low timer variable
unsigned long AUX1 = 0;                       // Pulse high timer variable
extern volatile unsigned long timer0_millis;  // External variable used by millis() command
unsigned long timeToGo = 4294967296-10000;    // Variable to set millis() value to 10 seconds before rollover


void setup() {
  setupPLC();                                 // Define inputs and outputs
  Serial.begin(57600);                        // Enable serial monitor (57600 Baud)
  noInterrupts ();                            // Set millis() to 10 seconds before rollover
  timer0_millis = timeToGo;
  interrupts ();
}

void loop() {
  in (X0);                                    // Read Enable input (1 = enable)
  timerCycle(AUX0, 900, AUX1, 100);           // Repeating pulse, low = 0.9 s, high = 0.1 s
                                              // (hence period = 1 second)
  out(Y0);                                    // Send pulse waveform to Output 0
  
  Serial.print(" Millis: ");                  // Display millis() value to view rollover
  Serial.println(millis()/1000);
  delay(10);
}
