/******************************************************************
*	Author(s): Team sudo rm -rf /
*	Last Modified: 1/24/13 by Cody Bulkley
*
*	Function Name: PumpControl
*   
*	Description: This function will take the past in values to 
*		determine which pump turn on, and for how long. It does 
*		support accepting values for no pumps to turn on, as well
*		 as turning on two pumps at the same time. 
*
*   Output: This allows for full control of the fluid pumps,
*		and will return 1 if a pump was turned on, or it will
*		return 0 if no pump was turned on. 
*******************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int PumpControl (int pump_select, int time_interval)
{	
	int success = 0;									// returns 1 if either pump successfully turns on
	int i = 0;
printf ("From %d",pump_select);
	switch (pump_select)
	{													// pump 1 is PiGPIO pin 0 (11 on board)
		case 1:											// pump 2 is PiGPIO pin 2 (13 on board)	
		{
			printf ("\nDispensing!");
			digitalWrite (0, 1);						// pump 1 is enabled and on
			
			for (i = 0; i < time_interval; i++)			// the pump will loop for the amount past in
			{	}										// based on the interval for each cup size
					
			digitalWrite (0, 0);						// turn the pump off
			success = 1;								// successful pump sequence
			
			break;
		}
		case 2:
		{
			digitalWrite (2, 1);						// pump 2 is enabled and on
			printf ("\nDispensing!");
			for (i = 0; i < time_interval; i++)			// the pump will loop for the amount past in
			{	}										// based on the interval for each cup size
					
			digitalWrite (2, 0);						// turn the pump off
			success = 1;								// successful pump sequence
			
			break;
		}
		case 3:
		{
			// **** both pumps are enabled  ****
			// **** careful using this mode ****
			digitalWrite (0, 1);						// pump 1 is enabled and on
			digitalWrite (2, 1);						// pump 2 is enabled and on
			printf ("\nDispensing!");
			for (i = 0; i < (time_interval/2); i++)			// the pump will loop for the amount past in
			{	}										// based on the interval for each cup size
					
			digitalWrite (0, 0);						// turn pump 1 off
			digitalWrite (2, 0);						// turn pump 2 off
			success = 1;								// successful pump sequence
			
			break;
		}
		default:
		{
			printf ("From %d",pump_select);											// no pumps are enabled
			digitalWrite (0, 0);						// make sure pump 1 is off
			digitalWrite (2, 0);						// make sure pump 2 is off
			success = 0;								// non-successful pump sequence
			break;
		}
	}							
	
	return success;										// returns 1 if a pump sequence occured,
														// or 0 if no pump was enabled
}
