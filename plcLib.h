/*
  plcLib Version 1.1.0, last updated 16 May, 2015.
  
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

#ifndef plcLib_h
#define plcLib_h

#include "Arduino.h"

// Define basic I/O pins for Arduino Uno and compatibles
const int X0 = A0;
const int X1 = A1;
const int X2 = A2;
const int X3 = A3;

const int Y0 = 3;
const int Y1 = 5;
const int Y2 = 6;
const int Y3 = 9;

// Define Motor Shield pin names
const int DIRA = 12;
const int DIRB = 13;
const int PWMA = 3;
const int PWMB = 11;
const int BRAKEA = 9;
const int BRAKEB = 8;
const int CURRENTA = A0;
const int CURRENTB = A1;

// Define additional I/O pins for Mega, Mega 2560 and Due
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)
const int X4 = A6;
const int X5 = A7;
const int X6 = A8;
const int X7 = A9;
const int Y4 = 4;
const int Y5 = 7;
const int Y6 = 8;
const int Y7 = 12;
#endif

void setupPLC();
unsigned int in(int input);
unsigned int in(unsigned int input);
unsigned int in(unsigned long input);
unsigned int inNot(int input);
unsigned int inNot(unsigned int input);
unsigned int inNot(unsigned long input);
unsigned int inAnalog(int input);
unsigned int inAnalog(unsigned int input);
unsigned int inAnalog(unsigned long input);
unsigned int out(int output);
unsigned int out(unsigned int &output);
unsigned int out(unsigned long &output);
unsigned int outNot(int output);
unsigned int outNot(unsigned int &output);
unsigned int outNot(unsigned long &output);
unsigned int outPWM(int output);
unsigned int andBit(int input);
unsigned int andBit(unsigned int input);
unsigned int andBit(unsigned long input);
unsigned int andNotBit(int input);
unsigned int andNotBit(unsigned int input);
unsigned int andNotBit(unsigned long input);
unsigned int orBit(int input);
unsigned int orBit(unsigned int input);
unsigned int orBit(unsigned long input);
unsigned int orNotBit(int input);
unsigned int orNotBit(unsigned int input);
unsigned int orNotBit(unsigned long input);
unsigned int xorBit(int input);
unsigned int xorBit(unsigned int input);
unsigned int xorBit(unsigned long input);
unsigned int latch(int output, int reset);
unsigned int latch(int output, unsigned int reset);
unsigned int latch(int output, unsigned long reset);
unsigned int latch(unsigned int &output, int reset);
unsigned int latch(unsigned long &output, int reset);
unsigned int latch(unsigned int &output, unsigned int reset);
unsigned int latch(unsigned long &output, unsigned long reset);
unsigned int timerOn(unsigned long &timerState, unsigned long timerPeriod);
unsigned int timerPulse(unsigned long &timerState, unsigned long timerPeriod);
unsigned int timerOff(unsigned long &timerState, unsigned long timerPeriod);
unsigned int timerCycle(unsigned long &timer1State, unsigned long timer1Period, unsigned long &timer2State, unsigned long timer2Period);
unsigned int compareGT(int input);
unsigned int compareGT(unsigned int input);
unsigned int compareGT(unsigned long input);
unsigned int compareLT(int input);
unsigned int compareLT(unsigned int input);
unsigned int compareLT(unsigned long input);
unsigned int set(int output);
unsigned int set(unsigned int &output);
unsigned int set(unsigned long &output);
unsigned int reset(int output);
unsigned int reset(unsigned int &output);
unsigned int reset(unsigned long &output);

class Counter
{
  public:
    Counter(unsigned int presetValue);
    Counter(unsigned int presetValue, unsigned int direction);
    void countUp();
    void countDown();
    void preset();
    void clear();
    unsigned int upperQ();
    unsigned int lowerQ();
    unsigned int count();
    unsigned int presetValue();
  private:
    unsigned int _pv;
    unsigned int _ct;
    unsigned int _ctUpEdge;
	unsigned int _ctDownEdge;
    unsigned int _uQ;
    unsigned int _lQ;
};

class Shift
{
  public:
    Shift();
	Shift(unsigned int sreg);
	unsigned int bitValue(unsigned int bitno);
	unsigned int value();
	void reset();
	void inputBit();
	void shiftLeft();
	void shiftRight();
  private:
    unsigned int _srLeftEdge;
    unsigned int _srRightEdge;
	unsigned int _sreg;
	unsigned int _inbit;
};

class Stack
{
  public:
    Stack();
	void push();
	void pop();
	void orBlock();
	void andBlock();
  private:
	unsigned long _sreg;
};

class Pulse
{
  public:
    Pulse();
	void inClock();
	void rising();
	void falling();
  private:
	unsigned int _pulseInput;
	unsigned int _pulseUpEdge;
	unsigned int _pulseDownEdge;
};

#endif
