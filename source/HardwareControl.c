#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "PumpControllingSystem.h"
#include "CupSenseT.h"
#include "defs.h"
#include "HardwareControl.h"
#include <pthread.h>
#include "unistd.h"
#include "UserButtons.h"

typedef struct soft_args soft_args;

void * enterControl( void * s_args)
{
    soft_args * args = (soft_args *)(s_args);
	short cup_data = 0;
	initSystem();
	initPumpPins();
    initServo();
	printf("Spinning up threads and preparing cup pins\n");
	init_cup_service();
	
	printf("Entering service loop\n");

	while(1) 
	{
		piLock(PMP_KEY);

        while ( cup_data = get_cup_data() == 0 )
            usleep(500);
        printf("HardwareControl found cup %d\n", cup_data);

        if ( cup_data == CUP_PIN_1 )
		    args->cup = 1;
        else if ( cup_data == CUP_PIN_2 )
		    args->cup = 2;
        else if ( cup_data == CUP_PIN_3 )
		    args->cup = 3;
		piLock(DAT_KEY);
		set_drink_size(args->size);
		set_pump_sel(args->pump_num);
        set_cup_data(0);
		piUnlock(DAT_KEY);
		piUnlock(PMP_KEY);

		usleep(500);
	}
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

void initServo(void)
{
	system("gpio mode 1 pwm");
	usleep(500);
	system("gpio pwm-ms");
	usleep(500);
	system("gpio pwmc 200");
	usleep(500);
	system("gpio pwm 1 0");
}
