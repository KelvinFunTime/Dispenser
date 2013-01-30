#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Pound_Defines.c"

/******************************************************************
*	Function Name: button_debounce
*   
*	Description: This function will take the past in value and
*		wait out the bounce of the button and check the button
*		again to see if its a successful push or release. If the 
*		user passes in a 0 they are debounce a press, if they pass
*		in a 1 they are debouncing a release.
*
*   Output: This function stores the return variable with a value 
*		according to if the press or release was successful or not.
*******************************************************************/
int button_debounce (int pin, int debounce_direction, int length)
{
	int count = 0;	  	// temp count variable		
	int success = 0;	// return value temp
	
	// will loop until there is no more bounce
	for (count; count < length; count++)					
		{	}
		
	// checks again to see if the condition is still met
	if (digitalRead(pin) == debounce_direction) 			
		// assigns the return variable to 1 indicating success
		success = 1;										
	
	// assigns the return variable to 0 indicating failure
	else
		success = 0;											
	
	return success;
}
