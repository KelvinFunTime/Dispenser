#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "CupSense.h"
#include "PumpControllingSystem.h"

void initSystem(void);
void senseCups(void);
void pumpAction(void);

int cup1serviced = 0;
int cup2serviced = 0;
int cup3serviced = 0;

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

	// If cup is held down and hasn't been serviced
	if(senseCup(1) == 0 && cup1serviced != 1)
	{
		// Turn servo here
		pumpAction();
		cup1serviced = 1;
	}
	else if(senseCup(1) == 1)	// If cup spot is empty, clear serviced flag
	{
		cup1serviced = 0;
	}
	
	if(senseCup(2) == 0 && cup2serviced != 1)
	{
		// Turn servo here
		pumpAction();
		cup2serviced = 1;
	}
	else if(senseCup(2) == 1)
	{
		cup2serviced = 0;
	}
	
	if(senseCup(3) == 0 && cup3serviced != 1)
	{
		// Turn servo here
		pumpAction();
		cup3serviced = 1;
	}
	else if(senseCup(3) == 1)
	{
		cup3serviced = 0;
	}
}

void pumpAction(void)
{
	printf("\nCUP SENSED\n");

	pump = PumpSelect();

	interval = SetCupSize();

	PumpControl(pump, interval);
	
	printf("\nThank You, Come Again!\n");
}
