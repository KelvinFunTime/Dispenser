#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "PumpControllingSystem.h"
#include "CupSenseT.h"
#include "defs.h"
#include "CupSense.h"
#include <pthread.h>

void initSystem(void);

int main(void)
{
	printf("Spinning up threads\n");
	initSystem();
	initPumpPins();
	initCupPins();

	init_cup_service();
	
	while(1)
	{
		piLock(PMP_KEY);
		while ( !get_cup_data() )
			usleep(500);
		set_cup_data(0);
		//Set pump stuff here
		piUnlock(PMP_KEY);
		usleep(500);
	}

	return 0;
}

void initSystem(void)
{
	printf("Checking wiringPi setup\n");
	int setupCheck = wiringPiSetup();	// WiringPi init

	while(setupCheck == -1)
	{
		// If you're stuck here, wiringPi failed to init
	}
	
	setupCheck = piHiPri(99);
	printf("Second while loop\n");
	while(setupCheck == -1)
	{
		// If you're stuck here, the Pi failed to be elevated to highest priority
	}
	printf("Set up finished\n");
}

