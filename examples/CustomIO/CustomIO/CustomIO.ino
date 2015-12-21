#define noPinDefs
#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Custom I/O - Define your own inputs and outputs from scratch
   
   Begin by including the line '#define noPinDefs' at the start, which prevents
   creation of standard inputs and output names X0, X1, ..., Y0, Y1, ... etc.
   (This option is available in plcLib V1.2.0 or greater.)
   
   The 'setupPLC();' command is not needed if you are using custom inputs
   and outputs.
   
   You can then define your own pin names, as required. Any 'unsigned integer'
   variables are treated as user defined variables, while 'integers' refer to
   local pin numbers. For example: -
   
        "unsigned int X1, Y1;" creates X1 and Y1 as user defined variables
        "int X0=A0, Y0=3, Y2=6;" creates X0, Y0 and Y2 as local pin names
   
   The next step is to define pins as either inputs or outputs by using the 
   "pinMode(pin, mode)" command. Sample configuration code has been placed in
   the 'customIO' function which is available from the IO tab and called from 
   within the 'setup()' function below.

   Software and Documentation:
   http://www.electronics-micros.com/software-hardware/plclib-arduino/

*/

unsigned int X1,Y1;        // Create variables X1 and Y1
int X0=A0, Y0=3, Y2=6;     // Create X0, Y0 and Y2 as local pins

void setup() {
  customIO();              // Setup input and output pin directions
}                          // (See IO tab for details)

void loop() {
  in(X0);                  // Read pin A0
  out(Y0);                 // Output to pin 3

  in(X1);                  // Read variable X1 (=0 by default)
  outNot(Y1);              // Send inverted value (1) to variable Y1
  
  in(Y1);                  // Read variable Y1
  out(Y2);                 // Output to pin 6
}