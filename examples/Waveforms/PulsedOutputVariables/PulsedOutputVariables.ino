#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Pulsed Output - Creating a repeating pulse using the timerCycle command, and
                   using variables to hold pulse low and pulse high times

   Connections:
   Input - Enable input connected to input X0 (Arduino pin A0)
   Output - Pulse Waveform on LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

// Variables:
unsigned long AUX0 = 0;                 // Pulse low timer variable
unsigned long AUX1 = 900;               // Pulse low timer period variable = 0.9 seconds
unsigned long AUX2 = 0;                 // Pulse high timer variable
unsigned long AUX3 = 100;               // Pulse high timer period variable = 0.1 seconds
                                        // (hence period = 1 second)

void setup() {
  setupPLC();                           // Define inputs and outputs
}

void loop() {
  in (X0);                              // Read Enable input (1 = enable)
  timerCycle(AUX0, AUX1, AUX2, AUX3);   // Repeating pulse, low = 0.9 s, high = 0.1 s
  out(Y0);                              // Send pulse waveform to Output 0
}
