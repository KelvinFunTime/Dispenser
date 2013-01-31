#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "cup_sense.h"
#include "PumpControllingSystem.h"

void initSystem(void);
void senseCups(void);

int main(void)
{
	initSystem();
	initCupPins();
	initPumpPins();

	while(1)
	{
		senseCups();
		usleep(500);
	}

	return 0;
}

void initSystem(void)
{
	int setupCheck = wiringPiSetup();	// WiringPi init
	
	while(setupCheck == -1)
	{
		// If you're stuck here, wiringPi failed to init
	}
	
	setupCheck = piHiPri(99);
	
	while(setupCheck == -1)
	{
		// If you're stuck here, the Pi failed to be elevated to highest priority
	}
}

void senseCups(void)
{
	int pump = 0;
	int interval = 0;

	if(senseCup(1) == 0)
	{
		printf("\nCUP 1\n");

		pump = PumpSelect ();

		interval = SetCupSize ();

		PumpControl (pump, interval);
		
		printf ("\nThank You, Come Again!\n");
	}
}
