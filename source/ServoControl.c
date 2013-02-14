#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>

//#define PWN_PIN 12	// gpio 18, pi 12
//#define PWM_OUTPUT	2
#define SW_PWM 0 //(gpio 0, pin 11)
int main ()
{
	// pinMode(PWM_PIN,PWM_OUTPUT); //setup hardware pwm
	softPwmCreate(SW_PWM,0,100); //setup software pwm pin 

	if ( wiringPiSetup() == -1 )
		return 1;
		
	softPwmWrite (SW_PWM, 500);	

	while (1);
	
	return 0;
}