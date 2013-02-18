#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "CupSense.h"
#include "PumpControllingSystem.h"
#include "CupSenseT.h"

void initSystem(void);

int main(void)
{
	initSystem();
	initCupPins();
	initPumpPins();
	init_cup_service();
	
	while(1)
	{
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

