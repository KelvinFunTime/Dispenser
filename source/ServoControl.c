#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

//#define PWN_PIN 12	// gpio 18, pi 12
//#define	PWM_OUTPUT	2
#define SW_PWM 0 //(gpio 0, pin 11)
int main ()
{
	int i = 0;
	int j = 20;
	
	// pinMode(PWM_PIN,PWM_OUTPUT); //setup hardware pwm
	softPwmCreate(SW_PWM,0,100); //setup software pwm pin 
	if ( wiringPiSetup() == -1 )
		return 1;
		
	softpwnWrite (SW_PWM, 500);	
	
	return 0;
}