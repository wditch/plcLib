#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Velleman IO Shield Input / Output mapping

   Bare Minimum - Single bit digital input and output

   Connections:
   6 digital inputs D0-D5 (Arduino pins 2, 3, 4, 5, 6 and 7)
   6 analogue inputs A0-A5 (connected to the same Arduino pins)
   6 relay outputs R0-R5 (Arduino pins 8, 9, 10,11, 12 and 13)
   
   Note: outPWM() and outServo() commands should not be used with this
         board due to the use of mechanical switch-based relay outputs.

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

                     // Define digital input pins x 6
  const int D0 = 2;
  const int D1 = 3;
  const int D2 = 4;
  const int D3 = 5;
  const int D4 = 6;
  const int D5 = 7;
  
                     // Analogue pins will use existing names A0 - A5
  
                     // Define Relay outputs as R0 - R7
  const int R0 = 8;
  const int R1 = 9;
  const int R2 = 10;
  const int R3 = 11;
  const int R4 = 12;
  const int R5 = 13;


void setup() {
  vellemanIO();  // Setup inputs and outputs for Velleman IO Shield
}

void loop() {
  in(D0);      // Read Digital Input 0
  out(R0);     // Send to Output 0 (Relay 1 of 6)
}

void vellemanIO (){
  
  // Input pin directions
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  // Relay Output pin directions
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
}