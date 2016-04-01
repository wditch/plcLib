/*
  plcLib Version 1.3.0, last updated 1 April, 2016.
  
  A simple Programmable Logic Controller (PLC) library for the
  Arduino and compatibles.

  Author:    W. Ditch
  Publisher: www.electronics-micros.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details, available from:
  <http://www.gnu.org/licenses/>
*/

#include "Arduino.h"
#include "plcLib.h"

extern unsigned int scanValue = 0;

// Define array size for pin monitoring
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)
	#define maxPins 70                    // Set maxPins to 70 if Arduino Mega or Due are detected
#else
	#define maxPins 20                    // otherwise set maxPins to 20
#endif                                    // maxPins value is returned by serial monitor P command

// Define serial monitor status bit positions for pinStatusUpdate function (0=RHS, 7=LHS)
#define pinUsedFlag 7                     // Value = 128 if active
#define reportingEnabledFlag 6            // Value = 64 if active
#define digitalInputFlag 5                // Value = 32 if active
#define analogInputFlag 4                 // Value = 16 if active
#define digitalOutputFlag 3               // Value = 8 if active
#define analogOutputFlag 2                // Value = 4 if active
#define servoOutputFlag 1                 // Value = 2 if active
#define pinUpdatedFlag 0                  // Value = 1 if active

// Define variables used by serial command monitor
String serialCommand = "";                // Create text string for serial commands
String serialCommandArgument = "";        // Create text string for serial command argument
boolean serialCommandFlag = false;        // Flag to indicate a command is available
boolean serialFirstRun = true;            // Flag to trigger serial Monitor initialisation
String appName = "plcLib";                // Appname returned by serial monitor A command
char appMajorVersion = '1';               // Major version returned by serial monitor M command
char appMinorVersion = '3';               // Minor version returned by serial monitor m command

// Create a 'struct' data type to hold serial monitor pin values
typedef struct
  {
      byte statusValue = 0;
      unsigned int previousValue = 0;
  } pinValueType;

// Initialise pin value struct
pinValueType pinValue[maxPins];
// Values can be accessed using pinValue[pin].statusValue
// or pinValue[pin].previousValue

// Define default pin directions and initial output levels.
// (or leave these unconfigured if noPinDefs is set in the user sketch)
void setupPLC() {
    #ifndef noPinDefs
	// Basic input pins
	pinMode(X0, INPUT);
	pinMode(X1, INPUT);
	pinMode(X2, INPUT);
	pinMode(X3, INPUT);
	
	// Basic output pins
	pinMode(Y0, OUTPUT);
	pinMode(Y1, OUTPUT);
	pinMode(Y2, OUTPUT);
	pinMode(Y3, OUTPUT);

	// Additional pins for Mega, Mega 2560 and Due boards
	#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)
		pinMode(X4, INPUT);
		pinMode(X5, INPUT);
		pinMode(X6, INPUT);
		pinMode(X7, INPUT);
		pinMode(Y4, OUTPUT);	
		pinMode(Y5, OUTPUT);
		pinMode(Y6, OUTPUT);	
		pinMode(Y7, OUTPUT);
		
	#endif /* Additional pins for Mega, Mega 2560 and Due boards */

	//Motor Shield pins
	pinMode(DIRA, OUTPUT);
	pinMode(DIRB, OUTPUT);
	pinMode(PWMA, OUTPUT);
	pinMode(PWMB, OUTPUT);
	pinMode(BRAKEA, OUTPUT);	
	pinMode(BRAKEB, OUTPUT);
	pinMode(CURRENTA, INPUT);	
	pinMode(CURRENTB, INPUT);
	// (The Motor Shield also has four Tinkerkit compatible pins.
	// These are inputs X2-X3/A2-A3/I2-I3 and outputs Y1-Y2/D5-D6/O4-O3.)
	
	// Default output port values
	digitalWrite(Y0, LOW);
	digitalWrite(Y1, LOW);
	digitalWrite(Y2, LOW);
	digitalWrite(Y3, LOW);
	#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)
	digitalWrite(Y4, LOW);
	digitalWrite(Y5, LOW);
	digitalWrite(Y6, LOW);
	digitalWrite(Y7, LOW);
	#endif /* if defined Mega, Mega 2560 and Due */
	digitalWrite(DIRA, LOW);
	digitalWrite(DIRB, LOW);
	digitalWrite(PWMA, LOW);
	digitalWrite(PWMB, LOW);
	digitalWrite(BRAKEA, LOW);		// Channel A Brake off
	digitalWrite(BRAKEB, LOW);		// Channel B Brake off
	#endif /* noPinDefs */
}

// Read an input pin (pin number supplied as integer)
unsigned int in(int input) {
	scanValue = digitalRead(input);
	#ifdef monitorEnable
	  pinStatusUpdate(input, digitalInputFlag, scanValue);		// pin number = input, type = digital input, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Read an auxiliary input (variable supplied as unsigned integer)
unsigned int in(unsigned int input) {
	scanValue = input;
	return(scanValue);
}

// Read an auxiliary input (variable supplied as unsigned long)
unsigned int in(unsigned long input) {
	scanValue = input;
	return(scanValue);
}

// Read an inverted input (pin number supplied as integer)
unsigned int inNot(int input) {
	if (digitalRead(input) == 1) {
		scanValue = 0;
	}
	else {
		scanValue = 1;
	}
	#ifdef monitorEnable
	  pinStatusUpdate(input, digitalInputFlag, scanValue);		// pin number = input, type = digital input, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Read an inverted auxiliary input (variable supplied as unsigned integer)
unsigned int inNot(unsigned int input) {
	if (input == 1) {
		scanValue = 0;
	}
	else {
		scanValue = 1;
	}
	return(scanValue);
}

// Read an inverted auxiliary input (variable supplied as unsigned long)
unsigned int inNot(unsigned long input) {
	if (input == 1) {
		scanValue = 0;
	}
	else {
		scanValue = 1;
	}
	return(scanValue);
}

// Read an analogue input (input pin supplied as an integer)
unsigned int inAnalog(int input) {
	scanValue = analogRead(input);
	#ifdef monitorEnable
	  pinStatusUpdate(input, analogInputFlag, scanValue);		// pin number = input, type = analogue input, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Read an analogue auxiliary value (variable supplied as an unsigned integer)
unsigned int inAnalog(unsigned int input) {
	scanValue = input;
	return(scanValue);
}

// Read an analogue auxiliary value (variable supplied as an unsigned long)
unsigned int inAnalog(unsigned long input) {
	scanValue = input;
	return(scanValue);
}

// Output to an output pin
unsigned int out(int output) {
	if (scanValue == 1) {
		digitalWrite(output, HIGH);
	}
	else {
		digitalWrite(output, LOW);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Output to an auxiliary variable (variable type = unsigned integer)
unsigned int out(unsigned int &output) {
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}

// Output to an auxiliary variable (variable type = unsigned long)
unsigned int out(unsigned long &output) {
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}

// Output to an output pin (inverted)
unsigned int outNot(int output) {
	if (scanValue == 1) {
		digitalWrite(output, LOW);
	}
	else {
		digitalWrite(output, HIGH);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Output to an auxiliary variable (inverted) (variable type = unsigned integer)
unsigned int outNot(unsigned int &output) {
	if (scanValue == 1) {
		output = 0;
	}
	else {
		output = 1;
	}
	return(scanValue);
}

// Output to an auxiliary variable (inverted) (variable type = unsigned long)
unsigned int outNot(unsigned long &output) {
	if (scanValue == 1) {
		output = 0;
	}
	else {
		output = 1;
	}
	return(scanValue);
}

// Output a PWM value to an output pin (scanValue in range 0-1023)
unsigned int outPWM(int output) {
	analogWrite(output, scanValue / 4);
	#ifdef monitorEnable
	  pinStatusUpdate(output, analogOutputFlag, scanValue);		// pin number = output, type = analogue output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// AND scanValue with input (pin number supplied as integer)
unsigned int andBit(int input) {
	scanValue = scanValue & digitalRead(input);
	return(scanValue);
}

// AND scanValue with auxiliary variable (variable supplied as unsigned integer)
unsigned int andBit(unsigned int input) {
	scanValue = scanValue & input;
	return(scanValue);
}

// AND scanValue with auxiliary variable (variable supplied as unsigned long)
unsigned int andBit(unsigned long input) {
	scanValue = scanValue & input;
	return(scanValue);
}

// AND scanValue with inverted input (pin number supplied as integer)
unsigned int andNotBit(int input) {
	scanValue = scanValue & ~digitalRead(input);
	return(scanValue);
}

// AND scanValue with inverted auxiliary variable (variable supplied as unsigned integer)
unsigned int andNotBit(unsigned int input) {
	scanValue = scanValue & ~input;
	return(scanValue);
}

// AND scanValue with inverted auxiliary variable (variable supplied as unsigned long)
unsigned int andNotBit(unsigned long input) {
	scanValue = scanValue & ~input;
	return(scanValue);
}

// OR scanValue with input (pin number supplied as integer)
unsigned int orBit(int input) {
	scanValue = scanValue | digitalRead(input);
	return(scanValue);
}

// OR scanValue with auxiliary variable (variable supplied as unsigned integer)
unsigned int orBit(unsigned int input) {
	scanValue = scanValue | input;
	return(scanValue);
}

// OR scanValue with auxiliary variable (variable supplied as unsigned long)
unsigned int orBit(unsigned long input) {
	scanValue = scanValue | input;
	return(scanValue);
}

// OR scanValue with inverted input (pin number supplied as integer)
unsigned int orNotBit(int input) {
	if (scanValue == 1) {
	}
	else {
		if (digitalRead(input) == 0) {
			scanValue = 1;
		}
		else {
			scanValue = 0;
		}
	}
	return(scanValue);
}

// OR scanValue with inverted auxiliary variable (variable supplied as unsigned integer)
unsigned int orNotBit(unsigned int input) {
	if (scanValue == 1) {
	}
	else {
		if (input == 0) {
			scanValue = 1;
		}
		else {
			scanValue = 0;
		}
	}
	return(scanValue);
}

// OR scanValue with inverted auxiliary variable (variable supplied as unsigned long)
unsigned int orNotBit(unsigned long input) {
	if (scanValue == 1) {
	}
	else {
		if (input == 0) {
			scanValue = 1;
		}
		else {
			scanValue = 0;
		}
	}
	return(scanValue);
}

// XOR scanValue with input (pin number supplied as integer)
unsigned int xorBit(int input) {
	scanValue = scanValue ^ digitalRead(input);
	return(scanValue);
}

// XOR scanValue with auxiliary variable (variable supplied as unsigned integer)
unsigned int xorBit(unsigned int input) {
	scanValue = scanValue ^ input;
	return(scanValue);
}

// XOR scanValue with auxiliary variable (variable supplied as unsigned long)
unsigned int xorBit(unsigned long input) {
	scanValue = scanValue ^ input;
	return(scanValue);
}

// Set - Reset latch (output and reset pin numbers supplied as integers)
unsigned int latch(int output, int reset) {
	scanValue = scanValue | digitalRead(output);		// Self latch by ORing with Output pin (Q)
	scanValue = scanValue & ~digitalRead(reset);		// AND-Not with Reset Pin
	if (scanValue == 1) {
		digitalWrite(output, HIGH);
	}
	else {
		digitalWrite(output, LOW);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Set - Reset latch (output pin number supplied as integer, reset as unsigned integer variable)
unsigned int latch(int output, unsigned int reset) {
	scanValue = scanValue | digitalRead(output);		// Self latch by ORing with Output pin (Q)
	scanValue = scanValue & ~reset;						// AND-Not with Reset variable
	if (scanValue == 1) {
		digitalWrite(output, HIGH);
	}
	else {
		digitalWrite(output, LOW);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Set - Reset latch (output pin number supplied as integer, reset as unsigned long variable)
unsigned int latch(int output, unsigned long reset) {
	scanValue = scanValue | digitalRead(output);		// Self latch by ORing with Output pin (Q)
	scanValue = scanValue & ~reset;						// AND-Not with Reset variable
	if (scanValue == 1) {
		digitalWrite(output, HIGH);
	}
	else {
		digitalWrite(output, LOW);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Set - Reset latch (output as unsigned integer variable and reset pin as integer)
unsigned int latch(unsigned int &output, int reset) {
	scanValue = scanValue | output;						// Self latch by ORing with Output pin (Q)
	scanValue = scanValue & ~digitalRead(reset);		// AND-Not with Reset Pin
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}

// Set - Reset latch (output as unsigned long variable and reset pin as integer)
unsigned int latch(unsigned long &output, int reset) {
	scanValue = scanValue | output;						// Self latch by ORing with Output pin (Q)
	scanValue = scanValue & ~digitalRead(reset);		// AND-Not with Reset Pin
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}

// Set - Reset latch (output and reset values are unsigned integer auxiliary variables)
unsigned int latch(unsigned int &output, unsigned int reset) {
	scanValue = scanValue | output;				// Self latch by ORing with Output variable (Q)
	scanValue = scanValue & ~reset;				// AND-Not with Reset variable
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}

// Set - Reset latch (output and reset values are unsigned long auxiliary variables)
unsigned int latch(unsigned long &output, unsigned long reset) {
	scanValue = scanValue | output;				// Self latch by ORing with Output variable (Q)
	scanValue = scanValue & ~reset;				// AND-Not with Reset variable
	if (scanValue == 1) {
		output = 1;
	}
	else {
		output = 0;
	}
	return(scanValue);
}
// On delay timer - requires continuously enabled input from previous scanValue
// (timerState and timerPeriod are unsigned long values - 32 bit)
unsigned int timerOn(unsigned long &timerState, unsigned long timerPeriod) {
	if (scanValue == 0) {									// timer is disabled
		timerState = 0;										// Clear timerState (0 = 'not started')
	}
	else {													// Timer is enabled
		if (timerState == 0) {								// Timer hasn't started counting yet
			timerState = millis();							// Set timerState to current time in milliseconds
			scanValue = 0;									// Result = 'not finished' (0)
		}
		else {												// Timer is active and counting
			if (millis() - timerState >= timerPeriod) {		// Timer has finished
				scanValue = 1;								// Result = 'finished' (1)
			}
			else {											// Timer has not finished
				scanValue = 0;								// Result = 'not finished' (0)
			}
		}
	}
	return(scanValue);										// Return result (1 = 'finished',
                                                            // 0 = 'not started' / 'not finished')
}

// Fixed width pulse - enabled by momentary input from previous scanValue 
// (timerState and timerPeriod are unsigned long values - 32 bit)
unsigned int timerPulse(unsigned long &timerState, unsigned long timerPeriod) {
	if (scanValue == 1 || timerState != 0){					// Timer is enabled
		if (timerState == 0) {								// Timer hasn't started counting yet
			timerState = millis();							// Set timerState to current time in milliseconds
			scanValue = 1;									// Pulse = 'Active' (1)
		}
		else {												// Timer is active and counting
			if (millis() - timerState >= timerPeriod) {		// Timer has finished
			    if (scanValue == 0) {                       // Finished AND trigger is low
				    timerState = 0;							// Re-enabled timer
					scanValue = 0;							// Pulse = 'finished' (0)
				}
				else {                                      // Finished but trigger is still high
					scanValue = 0;                          // Wait for trigger to go low before re-enabling
				}
			}
			else {											// Timer has not finished
				scanValue = 1;								// Pulse = 'Active' (1)
			}
		}
	}
	return(scanValue);										// Return result (1 = 'active',
															// 0 = 'not started' / 'not yet re-enabled')
}
// Off delay timer - turns on immediately when enabled, then delays turning off when previous scanValue goes low
// (timerState and timerPeriod are unsigned long values - 32 bit)
unsigned int timerOff(unsigned long &timerState, unsigned long timerPeriod) {
	if (scanValue == 0) {									// Timer input is off (scanValue = 0)
		if (timerState == 0) {								// Timer is not started so do nothing
		}
		else {												// Timer is active and counting
			if (millis() - timerState >= timerPeriod) {		// Timer has finished
				scanValue = 0;								// Result = 'turn-off delay finished' (0)
			}
			else {											// Timer has not finished
				scanValue = 1;								// Result = 'turn-off delay not finished' (1)
			}
		}
	}
	else {													// Timer input is high (scanValue = 1)
		timerState = millis();								// Set timerState to current time in milliseconds
	}
	return(scanValue);										// Return result (1 = 'pulse On' / 'turn-off delay in progress',
															// 0 = 'not started' / 'finished')
}

// Cycle timer - creates a repeating pulse waveform when enabled by previous scanValue
// (timer1State, timer1Period, timer2State, timer2Period are unsigned long values - 32 bit)
unsigned int timerCycle(unsigned long &timer1State, unsigned long timer1Period, unsigned long &timer2State, unsigned long timer2Period) {
	if (scanValue == 0) {									// Enable input is off (scanValue = 0)
		timer2State = 0;									// Ready to start LOW pulse period when enabled
		timer1State = 1;
	}
	else {													// Enabled
		if (timer2State == 0) {								// Low pulse Active
			if (timer1State == 1) {							// LOW pulse period starting
				timer1State = millis();						// Set timerState to current time in milliseconds
			}
			else if (millis() - timer1State >= timer1Period) {	// Low pulse period has finished
				timer1State = 0;	
				timer2State = 1;							// Ready to start HIGH pulse period
			}
			scanValue = 0;									// Result = 'Pulse LOW' (0)
		}
		if (timer1State == 0) {								// High pulse Active
			if (timer2State == 1) {							// HIGH pulse period starting
				timer2State = millis();						// Set timerState to current time in milliseconds
			}
			else if (millis() - timer2State >= timer2Period) {	// High pulse has finished
				timer2State = 0;	
				timer1State = 1;							// Ready to start LOW pulse period
			}
			scanValue = 1;									// Result = 'Pulse HIGH' (1)
		}
	}
	return(scanValue);
}

// Test whether an analogue input is greater than a second analogue input
unsigned int compareGT(int input) {
	if (scanValue > analogRead(input)) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Test whether an analogue input is greater than a fixed unsigned int value
unsigned int compareGT(unsigned int input) {
	if (scanValue > input) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Test whether an analogue input is greater than a fixed unsigned long value
unsigned int compareGT(unsigned long input) {
	if (scanValue > input) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Test whether an analogue input is less than a second analogue input
unsigned int compareLT(int input) {
	if (scanValue < analogRead(input)) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Test whether an analogue input is less than a fixed unsigned int value
unsigned int compareLT(unsigned int input) {
	if (scanValue < input) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Test whether an analogue input is less than a fixed unsigned long value
unsigned int compareLT(unsigned long input) {
	if (scanValue < input) {
		scanValue = 1;
	}
	else {
		scanValue = 0;
	}
	return(scanValue);
}

// Set a latched output (output pin number supplied as integer)
unsigned int set(int output) {
	scanValue = scanValue | digitalRead(output);		// Self latch by ORing with Output pin
	if (scanValue == 1) {
		digitalWrite(output, HIGH);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// Set a latched output (variable supplied as unsigned integer)
unsigned int set(unsigned int &output) {
	scanValue = scanValue | output;		// Self latch by ORing with Output pin
	if (scanValue == 1) {
		output = 1;
	}
	return(scanValue);
}

// Set a latched output (variable supplied as unsigned long)
unsigned int set(unsigned long &output) {
	scanValue = scanValue | output;		// Self latch by ORing with Output pin
	if (scanValue == 1) {
		output = 1;
	}
	return(scanValue);
}

// reset (or clear) a latched output (output pin number supplied as integer)
unsigned int reset(int output) {
	if (scanValue == 1) {
		digitalWrite(output, LOW);
	}
	#ifdef monitorEnable
	  pinStatusUpdate(output, digitalOutputFlag, scanValue);		// pin number = output, type = digital output, command result = scanValue
	#endif /* serial monitor is enabled */
	return(scanValue);
}

// reset (or clear) a latched output (variable supplied as unsigned integer)
unsigned int reset(unsigned int &output) {
	if (scanValue == 1) {
		output = 0;
	}
	return(scanValue);
}

// reset (or clear) a latched output (variable supplied as unsigned long)
unsigned int reset(unsigned long &output) {
	if (scanValue == 1) {
		output = 0;
	}
	return(scanValue);
}

// Up, down, or up-down counter
Counter::Counter(unsigned int pv)	// Counter constructor method
{									// (Default values are for an up counter)
	_pv = pv;						// Set preset value using supplied parameter
	_ct = 0;						// Running count = zero
	_uQ = 0;						// Up counter upper Q output = 0
	_lQ = 1;						// Down counter lower Q output = 1
	_ctUpEdge = 0;					// Prepare rising edge detect for up counter
	_ctDownEdge = 0;				// Prepare rising edge detect for down counter
}

Counter::Counter(unsigned int pv, unsigned int direction)	// Counter constructor method
{									// (Second parameter sets default direction)
	_pv = pv;						// Set preset value using supplied parameter
	if(direction == 0){				// Set start values for an up counter
		_ct = 0;					// Running count = zero
		_uQ = 0;					// Up counter upper Q output = 0
		_lQ = 1;					// Down counter lower Q output = 1
	}
	else {							// Set start values for a down counter
		_ct = _pv;					// Running count = preset value
		_uQ = 1;					// Up counter upper Q output = 1
		_lQ = 0;					// Down counter lower Q output = 0
	}
	_ctUpEdge = 0;					// Prepare rising edge detect for up counter
	_ctDownEdge = 0;				// Prepare rising edge detect for down counter
}

unsigned int Counter::presetValue()	// Return preset value method
{
	return(_pv);					// Return preset value
}	

void Counter::clear()				// Clear counter method
{
	if(scanValue == 1) {			// Enabled if scanValue = 1
		_ct = 0;					// Running count = 0
		_uQ = 0;					// Up counter upper Q output = 0
		_lQ = 1;					// Down counter lower Q output = 1
		_ctUpEdge = 0;				// Prepare rising edge detect for up counter
		_ctDownEdge = 0;			// Prepare rising edge detect for down counter
	}
}

void Counter::preset()				// Preset counter method
{
	if(scanValue == 1) {			// Enabled if scanValue = 1
		_ct = _pv;					// Running count = preset value
		_uQ = 1;					// Up counter upper Q output = 1
		_lQ = 0;					// Down counter lower Q output = 0
		_ctUpEdge = 0;				// Prepare rising edge detect for up counter
		_ctDownEdge = 0;			// Prepare rising edge detect for down counter
	}
}

unsigned int Counter::upperQ()		// Read up counter upper Q output method
{
	if (_uQ == 1){					// Set scanValue = 1 if upper Q = 1
		scanValue = 1;
	}
	else {
		scanValue = 0;				// Otherwise set scanValue = 0
	}
	return(_uQ);					// Return upper Q value
}

unsigned int Counter::lowerQ()		// Read down counter lower Q output method
{
	if (_lQ == 1){					// Set scanValue = 1 if lower Q = 1
		scanValue = 1;
	}
	else {
		scanValue = 0;				// Otherwise set scanValue = 0
	}
	return(_lQ);					// Return lower Q value
}

unsigned int Counter::count()		// Return current count value method
{
	return(_ct);					// Return count value
}

void Counter::countUp()				// Count up method
{
	if (_ct != _pv) {      			// Not yet finished counting so continue
		if (scanValue == 0) {		// clock = 0 so clear counter edge detect
			_ctUpEdge = 0;
		}
		else {						// Clock = 1
			if (_ctUpEdge == 0) {	// Rising edge detected so increment count
				_ctUpEdge = 1;		// Set counter edge
				_ct++;				// Increment count
				if(_ct == _pv) {	// Counter has reached final value
					_uQ = 1;		// Counter upper Q output = 1
					_lQ = 0;		// Counter lower Q output = 0
				}
				if(_ct != _pv){		// Counter is not yet finished
					_uQ = 0;		// Counter upper Q output = 0
					_lQ = 0;		// Counter lower Q output = 0
				}
			}
		}
	}
}

void Counter::countDown()			// Count down method
{
	if (_ct != 0) {					// Not yet finished so continue
		if (scanValue == 0) {		// clock = 0 so clear counter edge detect
			_ctDownEdge = 0;
		}
		else {						// Clock = 1
			if (_ctDownEdge == 0) {	// Rising edge detected so decrement count
				_ctDownEdge = 1;	// Set counter edge
				_ct--; 				// Decrement count
				if(_ct == 0) {		// Counter has reached final value
					_uQ = 0;		// Counter QUp output = 0
					_lQ = 1;		// Counter QDown output = 1
				}
				if(_ct != 0) {		// Counter is not yet finished
					_uQ = 0;		// Counter upper Q output = 0
					_lQ = 0;		// Counter lower Q output = 0
				}
			}
		}
	}
}

// Shift register
Shift::Shift()						// Shift register constructor method
{									// (Register width = 32 bits)
	_sreg = 0;						// Set  the shift register to zero
	_srLeftEdge = 0;				// Prepare rising edge detect for left shift
	_srRightEdge = 0;				// Prepare rising edge detect for right shift
}

Shift::Shift(unsigned int sreg)	    // Shift register constructor method
{									// (Register width = 32 bits)
	_sreg = sreg;					// Set initial value
	_srLeftEdge = 0;				// Prepare rising edge detect for left shift
	_srRightEdge = 0;				// Prepare rising edge detect for right shift
}

unsigned int Shift::bitValue(unsigned int bitno)	// Read a bit at a specified position
{
	if(bitRead(_sreg, bitno) == 1) {
		scanValue = 1;				// Tested bit = 1
	}
	else {
		scanValue = 0;				// Tested bit = 0
	}
	return(scanValue);				// Return tested bit value
}

unsigned int Shift::value()			// Return the current shift register value
{
	return(_sreg);
}

void Shift::reset()					// Reset the shift register if scanValue = 0
{
	if(scanValue == 1){
		_sreg = 0;					// Set  the shift register to zero
		_srLeftEdge = 0;			// Prepare rising edge detect for left shift
		_srRightEdge = 0;			// Prepare rising edge detect for right shift
		}
}

void Shift::inputBit()				// Set the input bit of the shift register
{
	if (scanValue == 0) {			// If scanValue = 0, clear input bit
		_inbit = 0;
	}
	else {							// Otherwise set the input bit
		_inbit = 1;
	}
}

void Shift::shiftRight()			// Shift right method
{
	if (scanValue == 0) {			// clock = 0 so clear shift right edge detect
		_srRightEdge = 0;
	}
	else {							// Clock = 1
		if (_srRightEdge == 0) {	// Rising edge detected so shift right
			_srRightEdge = 1;		// Set shift right edge detect
			_sreg = _sreg >> 1;		// Shift to the right
			if (_inbit == 1) {		// Shift-in new input bit at LHS
				bitSet(_sreg, 15);
			}
		}
	}
}

void Shift::shiftLeft()				// Shift left method
{
	if (scanValue == 0) {			// clock = 0 so clear shift left edge detect
		_srLeftEdge = 0;
	}
	else {							// Clock = 1
		if (_srLeftEdge == 0) {		// Rising edge detected so shift left
			_srLeftEdge = 1;		// Set shift left edge detect
			_sreg = _sreg << 1;		// Shift to the left
			if (_inbit == 1) {		// Shift-in new input bit at RHS
				bitSet(_sreg, 0);
			}
		}
	}
}

// Single-bit Software Stack
Stack::Stack()						// Stack constructor method
{									// (Register width = 32 bits)
	_sreg = 0;						// Set the stack to zero
}

void Stack::push()					// Push scanValue bit onto the stack method
{
	_sreg = _sreg >> 1;				// Shift stack 1-bit to the right
	if (scanValue == 1) {			// Shift-in scanValue bit at LHS
		bitSet(_sreg, 31);
	}
	else {
		bitClear(_sreg, 31);
	}
}

void Stack::pop()					// Pop scanValue bit from the stack method
{
	scanValue = bitRead(_sreg, 31);	// Set scanValue to leftmost bit of stack
	_sreg = _sreg << 1;				// Shift stack 1-bit to the left
}

void Stack::orBlock()				// OR scanValue with value Popped from stack method
{
	scanValue = scanValue | bitRead(_sreg, 31);	// OR scanValue with top of stack
	_sreg = _sreg << 1;				// Shift stack 1-bit to the left
}

void Stack::andBlock()				// AND scanValue with value Popped from stack method
{
	scanValue = scanValue & bitRead(_sreg, 31);	// AND scanValue with top of stack
	_sreg = _sreg << 1;				// Shift stack 1-bit to the left
}

// Single scan cycle Pulse with rising or falling edge detection
Pulse::Pulse()						// Pulse constructor method
{
	_pulseInput = 0;				// Set pulse input tracker to zero
	_pulseUpEdge = 0;				// Prepare rising edge detect
	_pulseDownEdge = 0;				// Prepare falling edge detect
}

void Pulse::inClock()				// Read the clock input method
{
	if (scanValue != _pulseInput) {	// Rising or falling edge detected
		if (scanValue == 1) {		// Rising edge detected
			_pulseUpEdge = 1;		// Set rising edge detect value
			_pulseDownEdge = 0;		// Clear falling edge detect value
			_pulseInput = 1;		// Pulse input tracker = 1
		}
		else {						// Falling edge detected
			_pulseUpEdge = 0;		// Clear rising edge detect value
			_pulseDownEdge = 1;		// Set falling edge detect value
			_pulseInput = 0;		// Pulse input tracker = 0
		}
	}
	else {							// No change detected
	_pulseUpEdge = 0;				// Set both edge detect values to zero
	_pulseDownEdge = 0;				// (and leave pulse tracker unchanged)
	}
}

void Pulse::rising()		        // Pulse rising edge detected method
{
	scanValue = _pulseUpEdge;		// scanValue = 1 if rising edge detected, 0 otherwise
}

void Pulse::falling()		        // Pulse falling edge detected method
{
	scanValue = _pulseDownEdge;		// scanValue = 1 if falling edge detected, 0 otherwise
}

// Serial monitor update pin status function
void pinStatusUpdate(int pin, byte type, unsigned int scanValue)
{
	bitSet(pinValue[pin].statusValue, type);               // Set pin type
	bitSet(pinValue[pin].statusValue, pinUsedFlag);        // Set pin used status bit
	if (pinValue[pin].previousValue != scanValue) {        // If scanValue has changed then ...
		pinValue[pin].previousValue = scanValue;           // update previousValue
		if (bitRead(pinValue[pin].statusValue, reportingEnabledFlag)) {  // If reporting on pin is enabled then ...
			bitSet(pinValue[pin].statusValue, pinUpdatedFlag);                // set pinUpdated flag
		}
	}
}

// Serial monitor function
void serialMonitor(char IoMap[])
{
	if (serialFirstRun){                            // If running for the first time then
		for (int x = 0; x < maxPins; x++){          // clear all pin values
			pinValue[x].statusValue = 0;
			pinValue[x].previousValue = 0;
		}
		serialFirstRun = false;
	}

	while (Serial.available()) {
		char serialChar = (char)Serial.read();      // Read character from serial port
		serialCommand += serialChar;                // Add character to command string
		if (serialChar == '\n') {                   // Detect newline as end of command
			serialCommandFlag = true;               // Set command available flag to True
		}
	}
	if(serialCommandFlag){
		boolean pinUpdated = false;                 // Local variable used by pin updated check (U command)
		char serialCommandName = serialCommand[0];  // Read first character as command name
		if (serialCommand.length() >= 1){
			serialCommandArgument = serialCommand.substring(1);
		}
		else{
			serialCommandArgument = "";
		}
		switch (serialCommandName) {
			case 'A':                               // Command is "Read Application Name" - returns 'plcLib'
			Serial.println(appName);
			break;

			case 'a':                               // Command is "Read IO Map Name" - returns value supplied as IoMap parameter
			if(IoMap != ""){                        // to serial monitor command. E.g. serialMonitor("Basic");, or ...
				Serial.println(IoMap);
			}
			else{
				Serial.println("Default");          // returns "Default" if IoMap variable is an empty string
			}
			break;

			case 'M':                               // Command is "Read Major Version" - returns 'x' if Version = x.y
			Serial.println(appMajorVersion);
			break;

			case 'm':                               // Command is "Read Minor Version" - returns 'y' if Version = x.y
			Serial.println(appMinorVersion);
			break;

			case 'P':                               // Command is "Read Maximum Number of Pins (returns 20 or 70 based on board detected)"
			Serial.println(maxPins);                // Valid pin range is 0 to (maxPins-1)
			break;

			case 'S':                               // Command is "Read Status of Specified Pin - e.g S12"
			Serial.println(pinValue[serialCommandArgument.toInt()].statusValue);
			break;                                  // Note: No range check or other error detection is performed

			case 'V':                               // Command is "Read Value of Specified Pin - e.g. V12"
			Serial.println(pinValue[serialCommandArgument.toInt()].previousValue);
			bitClear(pinValue[serialCommandArgument.toInt()].statusValue, pinUpdatedFlag);       // Clear pinUpdated flag
			break;                                  // Note: No range check or other error detection is performed

			case 'E':                               // Command is "Enable Status Updating of Specified Pin - e.g E12"
			bitSet(pinValue[serialCommandArgument.toInt()].statusValue, reportingEnabledFlag);   // Set reportingEnabled flag
			break;                                  // Note: No range check or other error detection is performed

			case 'e':                               // Command is "Disable Status Updating of Specified Pin - e.g e12"
			bitClear(pinValue[serialCommandArgument.toInt()].statusValue, reportingEnabledFlag); // Clear reportingEnabled flag
			bitClear(pinValue[serialCommandArgument.toInt()].statusValue, pinUpdatedFlag);       // Clear pinUpdated flag
			break;                                  // Note: No range check or other error detection is performed

			case 'U':                               // Command is "Read list of updated pins (comma separated list)"
			for(int x = 0; x < maxPins; x++){
				if(bitRead(pinValue[x].statusValue, pinUpdatedFlag)){  // Updated pin found
					if (pinUpdated == true){        // Not the first updated pin found
						Serial.print(',');          // Print ',' as parameter separator
					}
					Serial.print(x);                // Print updated pin number
					pinUpdated = true;
				}
			}
			if(pinUpdated == false){
				Serial.print('N');                  // Return 'N' if no pins have been updated since last check
			}
			Serial.println("");                     // Send newline at end
			break;
			
			default:                                // Unknown command - returns '?'
			Serial.println("?");
		}
		
		serialCommand="";                           // Clear command string
		serialCommandFlag = false;                  // Set command available flag to False
	}
}