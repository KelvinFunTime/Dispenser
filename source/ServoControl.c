#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

#define PWN_PIN 12	// gpio 18, pi 12
#define	PWM_OUTPUT	2

int main ()
{
	int i = 0;
	int j = 20;
	
	 pinMode(PWM_PIN,PWM_OUTPUT); //setup hardware pwm
	
	if ( wiringPiSetup() == -1 )
		return 1;
		
	
	for (i = 0; i < j; i++)
	{
		pwnWrite (PWM_PIN, i);
	}
	
	
	return 0;
}