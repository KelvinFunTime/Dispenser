#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Pound_Defines.c"
#include "ButtonDebounce.c"

/******************************************************************
*	Function Name: user_button_sensed
*   
*	Description: This function will examine the button signal to 
*		see if it was pressed or not. Once it has properly 
*		debounced the signal and confirms it is a legit press,
*		it will display to the screen that the user pressed a 
*		button.
*
*   Output: This function displays to the screen if the user
*		button is pressed.
*******************************************************************/
void user_button_sensed ()
{
	int debounce_successful = 0;
	int button_successful = 0;
	
	// debounce the button and check again
	debounce_successful = button_debounce (7, 1, USER_PRESS_DEBOUNCE_LENGTH);			
			
	// if there was indeed a button press
	if (debounce_successful == 1)										
	{			
		// print "button pressed" to the screen
		printf ("\nButton Pressed!\n");					
				
		// make sure the button is released 
		// before checking for another press
		do												
		{			
			// check to see if the button was released
			button_successful = button_debounce (7, 0, USER_PRESS_DEBOUNCE_LENGTH);
		} while (button_successful == 0);	// loop until released			
	}
}

/******************************************************************
*	Function Name: cup_button_sensed
*   
*	Description: This function will examine the button signal to 
*  		see if a cup was placed or not. Once it has properly 
*		debounced the signal and confirms there is a cup in place,
*		it will display to the screen that there is a cup in place,
*		and it will send a signal for the pump to start running for
*		a certain interval.
*
*   Output: This function displays to the screen if there is a cup
*		placed, and starts the pump.
*******************************************************************/
void cup_button_sensed ()
{
	int debounce_successful = 0;
	int i = 0;
	int button_successful = 0;

	// debounce the button and check again
	debounce_successful = button_debounce (5, 1, CUP_SENSE_DEBOUNCE_LENGTH);			
			
	// if there was indeed a button press
	if (debounce_successful == 1)										
	{
		// reset temp varible
		button_successful = 0;				
		// print "button pressed" to the screen
		printf ("\nCup Detected!\n");	

		// we will now show we have access to turn on the 
		// pump on command
		digitalWrite (0, 1);	
		printf ("\nPump Is Turned On!\n");
		
		//turn on the pump for certain time length		
		for (i = 0; i < 10000; i++)
		{	}
				
		// turn the pump off
		digitalWrite (0, 0);
			
		// make sure the button is released 
		// before checking for another press
		do												
		{			
			// check to see if the button was released
			button_successful = button_debounce (5, 0, CUP_SENSE_DEBOUNCE_LENGTH);
		} while (button_successful == 0);	// loop until released
				
		// reset temp variable
		button_successful = 0;					
	}
}