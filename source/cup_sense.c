#ifndef CUP_SENSE
#define CUP_SENSE
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "defs.h"

void initCupPins(void);
int senseCup(int cup);

void initCupPins(void)
{
	pinMode(CUP_PIN_1, INPUT);
	pullUpDnControl(CUP_PIN_1, PUD_UP);
}

int senseCup(int cup)
{
	int pin = 0;
	
	switch(cup)
	{
		case 1: pin = CUP_PIN_1; break;
		default: pin = CUP_PIN_1;
	}
	
	return digitalRead(pin);
}

#endif