#ifndef CUP_SENSE
#define CUP_SENSE
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "defs.h"
#include "CupSense.h"

void initCupPins(void)
{
	pinMode(CUP_PIN_1, INPUT);
	pullUpDnControl(CUP_PIN_1, PUD_UP);

	pinMode(CUP_PIN_2, INPUT);
	pullUpDnControl(CUP_PIN_2, PUD_UP);

	pinMode(CUP_PIN_3, INPUT);
	pullUpDnControl(CUP_PIN_3, PUD_UP);
}

int senseCup(int cupPin)
{
	int val = 0;

	switch(cupPin)
	{
		case 1:
			val = digitalRead(CUP_PIN_1); break;
		case 2:
			val = digitalRead(CUP_PIN_2); break;
		case 3:
			val = digitalRead(CUP_PIN_3); break;
		default:
			printf("Invalid cup pin");
	}

	return val;
}

#endif