#ifndef CUP_SENSE
#define CUP_SENSE
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "defs.h"
#include "cup_sense.h"

void initCupPins(void)
{
	pinMode(CUP_PIN_1, INPUT);
	pullUpDnControl(CUP_PIN_1, PUD_UP);
}

int senseCup(int cupPin)
{
	int dick = 0;

	if(cupPin == 1)
		dick = digitalRead(CUP_PIN_1);

	return dick;
}

#endif
