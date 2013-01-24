#ifndef CUP_SENSE
#define CUP_SENSE
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "defs.h"

void initCupPins(void (*function)(void));
void setCupISR(int cupPin, void (*function)(void));
int senseCup(int cupPin);

void initCupPins(void (*function)(void))
{
	pinMode(CUP_PIN_1, INPUT);
	pullUpDnControl(CUP_PIN_1, PUD_UP);
	
	setCupISR(CUP_PIN_1, function);
}

void setCupISR(int cupPin, void (*function)(void))
{
	wiringPiISR(cupPin, INT_EDGE_FALLING, function);
}

int senseCup(int cupPin)
{
	return digitalRead(cupPin);
}

#endif