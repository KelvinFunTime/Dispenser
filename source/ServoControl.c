#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "ServoControl.h"
#include "defs.h"

void pwm_control(short pos)
{
	char pwm_str[20];
	sprintf(pwm_str, "gpio pwm 1 %d", pos);
	printf("gpio pwm 1 %d\n", pos);
	system(pwm_str);
    usleep(1500000);
	system("gpio pwm 1 0");
}
