#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ButtonSense.c"
#include "Pound_Defines.c"

int main ()
{
	int button_successful = 0;
	int user_button_sense = 0;
	int cup_button_sense = 0;
	int combined_value = 0;
	
	printf ("Testing Button Sense\n\n");
	
	if (wiringPiSetup () == -1)
		exit (1);
		
	/* wiringPi Pin 7, Pin 7 on Board */
	pinMode (7, INPUT); 												

	/* makes pin 7 active high */
	pullUpDnControl (7, PUD_UP); 	

	/* wiringPi Pin 1, Pin 18 on Board */
	pinMode (5, INPUT); 												

	// makes pin 1 active high 
	pullUpDnControl (5, PUD_UP); 

	// wiringPi Pin 0, Pin 11 on Board
	pinMode (0 , OUTPUT);
	
	while (1)
	{
		// each loop this will check the state of the pins
		user_button_sense = (digitalRead(7));
		cup_button_sense = (digitalRead(5));
		
		// shifts over the bit so we can look at the 
		// cup sensed and user button sensed at the
		// same time
		user_button_sense = user_button_sense << 1;
		combined_value = user_button_sense & cup_button_sense;
		
		switch (combined_value)
		{
			case 0:
				{
					// no button sensed, do nothing
					break;
				}
			case 1:
				{
					// cup sensed
					cup_button_sensed ();
					break;
				}
			case 2:
				{
					// user button sensed
					user_button_sensed ();
					break;
				}
			case 3:
				{
					// both sensed, give priorty
					// to the user
					user_button_sensed ();
					cup_button_sensed ();
					break;
				}
			default:
				break;
		}
	}
	return 0;
}

