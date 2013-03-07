#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "defs.h"
#include "unistd.h"

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

	switch (pump_select)
	{													// pump 1 is PiGPIO pin 4 (16 on board)
		case 1:											// pump 2 is PiGPIO pin 5 (18 on board)
		{
			printf ("\nDispensing to Pump 1.....");
			digitalWrite (PUMP_PIN_1, 1);		    // pump 1 is enabled and on

            usleep(time_interval * 1000000 + 1000000);

			digitalWrite (PUMP_PIN_1, 0);				// turn the pump off
			success = 1;								// successful pump sequence

			break;
		}
		case 2:
		{
			digitalWrite (PUMP_PIN_2, 1);				// pump 2 is enabled and on
			printf ("\nDispensing to Pump 2....");

            usleep(time_interval * 1000000 + 1000000);

			digitalWrite (PUMP_PIN_2, 0);				// turn the pump off
			success = 1;								// successful pump sequence

			break;
		}
		case 3:
		{
			// **** both pumps are enabled  ****
			// **** careful using this mode ****
			digitalWrite (PUMP_PIN_1, 1);						// pump 1 is enabled and on
			digitalWrite (PUMP_PIN_2, 1);						// pump 2 is enabled and on
			printf ("\nDispensing to Pump 1 and Pump 2....");

            usleep(time_interval * 500000 + 1000000);

			digitalWrite (PUMP_PIN_1, 0);					// turn pump 1 off
			digitalWrite (PUMP_PIN_2, 0);					// turn pump 2 off
			success = 1;									// successful pump sequence

			break;
		}
		default:
		{											// no pumps are enabled
			digitalWrite (PUMP_PIN_1, 0);			// make sure pump 1 is off
			digitalWrite (PUMP_PIN_2, 0);			// make sure pump 2 is off
			success = 0;							// non-successful pump sequence
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

	}	while (cup_size < 0 || cup_size > 34);						// wont exit until valid cup size

	cup_size = (cup_size * 1.2);									// 1.2 seconds for each ounce

										// this gives correct timing per ounce
	return (cup_size);								// creates correct value for loop
}																	// according to cup size determined

void initPumpPins (void)
{
	// wiringPi Pin 4, Pin 16 on Board
	pinMode (PUMP_PIN_1, OUTPUT);

	// wiringPi Pin 5, Pin 18 on Board
	pinMode (PUMP_PIN_2, OUTPUT);

	digitalWrite (PUMP_PIN_1, 0);	// make sure pump 1 is off
	digitalWrite (PUMP_PIN_2, 0);	// make sure pump 2 is off
}

void pumpAction(void)
{
	int pump = 0;
	int interval = 0;

	pump = PumpSelect();

	interval = SetCupSize();

	PumpControl(pump, interval);

	printf("\nThank You, Come Again!\n");
}
