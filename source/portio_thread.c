/***************************************************************
*Purpose:
*	Contains thread used for portio.
*
*Inputs:
*	Receives commands from main_thread (pwm, pin number, etc)
*
*Outputs:
*	Sends out IO through the pins and can clear commands from
*	main_thread
*
****************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

//Function available for accessing pins
void portio(short pin_num, short direction, short * length, short * pwm, short * cmd);

/***************************************************************
*
*
*
****************************************************************/

void portio(short pin_num, short direction, short * length, short * pwm, short * cmd)
{
	pinMode (pin_num, direction);

}

