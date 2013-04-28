#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "ServoControl.h"
#include "Defs.h"

short prev_pwm = 103;

void PWMControl(short pos)
{
	char pwm_str[20];
    short walk = 0;

    if ( ( walk = prev_pwm - pos ) > 0)
    {
        for ( walk = (prev_pwm - pos); walk != 0; walk-- )
        {
            sprintf(pwm_str, "gpio pwm 1 %d", pos + walk);
            system(pwm_str);
            usleep(25000);
        }
    }
    else if ( ( walk = prev_pwm - pos ) < 0)
    {
        for ( walk = (prev_pwm - pos); walk != 0; walk++ )
        {
            sprintf(pwm_str, "gpio pwm 1 %d", pos + walk);
            system(pwm_str);
            usleep(25000);
        }
    }

    prev_pwm = pos;
    usleep(150000);
	system("gpio pwm 1 0");
}
