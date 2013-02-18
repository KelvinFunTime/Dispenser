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

void senseCups(void)
{
	static int cup1serviced = 0;
	static int cup2serviced = 0;
	static int cup3serviced = 0;
	int button1debounce = 0;
	int button2debounce = 0;
	int button3debounce = 0;
	int pump = 0;
	int interval = 0;

	// If cup is held down and hasn't been serviced
	if(senseCup(1) == 0 && cup1serviced != 1)
	{
		printf("\nCup 1!!\n");
		// Turn servo here
		pumpAction();
		cup1serviced = 1;
	}
	else if(senseCup(1) == 1)	// If cup spot is empty, clear serviced flag
	{
		button1debounce = debounce (1, CUP_SENSE_DEBOUNCE_LENGTH, 1);	// makes sure the button was released
		
		if (button1debounce == 1)	// if we had a valid removal
		{
			cup1serviced = 0;
			button1debounce = 0;
			
			usleep (2000000);	// NEED THREADS to function correct! it sleeps for 2 seconds before next cup can be placed here
		}
	}
	
	if(senseCup(2) == 0 && cup2serviced != 1)
	{
		// Turn servo here
		printf("\nCup 2\n");
		pumpAction();
		cup2serviced = 1;
	}
	
	else if(senseCup(2) == 1)	// If cup spot is empty, clear serviced flag
	{
		button2debounce = debounce (2, CUP_SENSE_DEBOUNCE_LENGTH, 1);	// makes sure the button was released
		
		if (button2debounce == 1)	// if we had a valid removal
		{
			cup2serviced = 0;
			button2debounce = 0;
			
			usleep (2000000);	// NEED THREADS to function correct! it sleeps for 2 seconds before next cup can be placed here
		}
	}
	
	if(senseCup(3) == 0 && cup3serviced != 1)
	{
		printf("\nCup 3\n");
		// Turn servo here
		pumpAction();
		cup3serviced = 1;
	}
	
	else if(senseCup(3) == 1)	// If cup spot is empty, clear serviced flag
	{
		button3debounce = debounce (3, CUP_SENSE_DEBOUNCE_LENGTH, 1);	// makes sure the button was released
		
		if (button3debounce == 1)	// if we had a valid removal
		{
			cup1serviced = 0;
			button3debounce = 0;
			
			usleep (2000000);	// NEED THREADS to function correct! it sleeps for 2 seconds before next cup can be placed here
		}
	}
}


#endif