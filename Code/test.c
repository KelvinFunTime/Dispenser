#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USER_PRESS_DEBOUNCE_LENGTH 437500
#define CUP_SENSE_DEBOUNCE_LENGTH 875000

void cup_button_sensed ();
void user_button_sensed ();
int button_debounce (int pin, int direction, int length);

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

	/* wiringPi Pin 5, Pin 18 on Board */
	pinMode (5, INPUT); 												

	// makes pin 5 active high 
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
		combined_value = 0;
		user_button_sense = user_button_sense << 1;
		combined_value = (user_button_sense | cup_button_sense);
	
		switch (combined_value)
		{
			case 2:
				{
					// cup sensed
					cup_button_sensed ();
					break;
				}
			case 1:
				{
					// user button sensed
					user_button_sensed ();
					break;
				}
			case 0:
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
	debounce_successful = button_debounce (7, 0, USER_PRESS_DEBOUNCE_LENGTH);			
			
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
			button_successful = button_debounce (7, 1, USER_PRESS_DEBOUNCE_LENGTH);
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
	debounce_successful = button_debounce (5, 0, CUP_SENSE_DEBOUNCE_LENGTH);			
			
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
		for (i = 0; i < (1673000000); i++)
		{	}
				
		// turn the pump off
		digitalWrite (0, 0);
			
		// make sure the button is released 
		// before checking for another press
		do												
		{			
			// check to see if the button was released
			button_successful = button_debounce (5, 0, CUP_SENSE_DEBOUNCE_LENGTH);
		} while (button_successful == 1);	// loop until released
				
		// reset temp variable
		button_successful = 0;					
	}
}

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

