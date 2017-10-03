#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Pulsed Output - Creating a repeating pulse using the timerCycle command

   Connections:
   Input - Enable input connected to input X0 (Arduino pin A0)
   Output - Pulse Waveform on LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

// Variables:
unsigned long AUX0 = 0;                 // Pulse low timer variable
unsigned long AUX1 = 0;                 // Pulse high timer variable


void setup() {
  setupPLC();                           // Define inputs and outputs
}

void loop() {
  in (X0);                              // Read Enable input (1 = enable)
  timerCycle(AUX0, 900, AUX1, 100);     // Repeating pulse, low = 0.9 s, high = 0.1 s
                                        // (hence period = 1 second)
  out(Y0);                              // Send pulse waveform to Output 0
}
