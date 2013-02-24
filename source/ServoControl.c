#include <stdio.h>
#include <wiringPi.h>

#define PWM_PIN 1	// gpio 18, pi 12

int main ()
{
	if ( wiringPiSetup() == -1 )	// sets up the wiring pi
		return 1;
		
	pwmSetClock (200);				// Sets the proper clock divider

	pinMode(PWM_PIN,PWM_OUTPUT); 	//setup hardware pwm
	
	
	while (1)
	{
		pwmWrite (PWM_PIN, 150);		// cup 2

		sleep (5);
		
		pwmWrite (PWM_PIN, 220);		// cup 1
		
		sleep (5);
		
		pwnWrite (PWM_PIN, 90);			// cup 3
		
		sleep (5);
	}
	
	return 0;
}
