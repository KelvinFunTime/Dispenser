#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "ServoControl.h"
#include "defs.h"

int pwm_control(short pos)
{
	int i = 0;
	if ( wiringPiSetupGpio() == -1 )	// sets up the wiring pi
		return 1;
	
	system("gpio pwm-ms");
	system("gpio pwmc 200");
	system("gpio pwm 1 %d", pos);

	return 0;
}
