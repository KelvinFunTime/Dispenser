#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

#define PWM_PIN 1	// gpio 18, pi 12

int main ()
{
	int i = 0;
	int j = 30;

	if ( wiringPiSetup() == -1 )
		return 1;

	pinMode(PWM_PIN,PWM_OUTPUT); //setup hardware pwm
	
	for (i = 0; i < j; i++)
		pwmWrite (PWM_PIN, i);

	while (1);
	
	return 0;
}