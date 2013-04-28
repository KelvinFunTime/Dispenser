extern "C"
{
#include <wiringPi.h>
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Defs.h"
#include "unistd.h"

int PumpControl (int pump_select, int time_interval)
{
	int success = 0;									// returns 1 if either pump successfully turns on

	switch (pump_select)
	{													// pump 1 is PiGPIO pin 4 (16 on board)
		case 1:											// pump 2 is PiGPIO pin 5 (18 on board)
		{
			printf ("\nDispensing to Pump 1.....");
			digitalWrite (PUMP_PIN_1, 1);		    // pump 1 is enabled and on

            usleep(time_interval * 1000000 + 1500000);

			digitalWrite (PUMP_PIN_1, 0);				// turn the pump off
			success = 1;								// successful pump sequence

			break;
		}
		case 2:
		{
			digitalWrite (PUMP_PIN_2, 1);				// pump 2 is enabled and on
			printf ("\nDispensing to Pump 2....");

            usleep(time_interval * 1000000 + 1500000);

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

            usleep(time_interval * 500000 + 1500000);

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

void InitPumpPins()
{
	// wiringPi Pin 4, Pin 16 on Board
	pinMode (PUMP_PIN_1, OUTPUT);

	// wiringPi Pin 5, Pin 18 on Board
	pinMode (PUMP_PIN_2, OUTPUT);

	digitalWrite (PUMP_PIN_1, 0);	// make sure pump 1 is off
	digitalWrite (PUMP_PIN_2, 0);	// make sure pump 2 is off
}
