#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PI_CLOCK 700000000

int PumpSelect (void)
{
	int pump = 0;
	
	do 
	{
		usleep(500);
		printf ("\nPlease Enter 1 for Pump 1, or 2 for Pump 2: ");
		
		scanf ("%d", &pump);
	} while (pump != 1 && pump != 2);
	
	return pump;
}


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

int SetCupSize (void)
{
	float cup_size = 0;
	
	do 
	{
		usleep(500);

		printf ("\nPlease Enter Your Cup Size (in ounces): ");		// Prompts user for cup size in oz
		scanf ("%f", &cup_size);										// gets user input for cup size
		
	}	while (cup_size < 0 && cup_size > 34);						// wont exit until valid cup size
	
	cup_size = (cup_size * 1.2);									// 1.2 seconds for each ounce
	cup_size = (int)((cup_size * PI_CLOCK)/10.5);	
										// this gives correct timing per ounce
	return (cup_size);								// creates correct value for loop
}																	// according to cup size determined

void initPumpPins (void)
{
	// wiringPi Pin 7, Pin 7 on Board 
	pinMode (7, INPUT); 												

	// makes pin 7 active high 
	pullUpDnControl (7, PUD_UP); 	

	// wiringPi Pin 2, Pin 13 on Board
	pinMode (2, OUTPUT); 												

	// wiringPi Pin 0, Pin 11 on Board
	pinMode (0 , OUTPUT);
}