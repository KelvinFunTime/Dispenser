#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "cup_sense.c"

void initSystem(void);
void senseCups(void);

void main(void)
{
	initSystem(void);
	initCupPins(void);
	
	while(1)
	{
		senseCups(void);
	}
}

void initSystem(void)
{
	int setupCheck = wiringPiSetup(void);	// WiringPi init
	
	while(setupCheck == -1)
	{
		// If you're stuck here, wiringPi failed to init
	}
	
	initCupPins(void);	// Cup buttons init
}

void senseCups(void)
{
	if(senseCup(1) == 0)
	{
		printf("CUP 1 LOLOLOLOLOLOLOLOL");
	}
}