#include "PortIO_Thread.h"
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "debounce.h"
#include "ServoControl.h"
#include "unistd.h"
#include "PumpControllingSystem.h"

/***************************************************************
*Name: 
*	port_input
*Inputs:
*	pin_num, pin to watch for.
*	deb_length, how long to debounce for.
*	*data, the pointer to write data to when a pin is high
*Outputs:
*	*data is updated whenever a pin goes high
****************************************************************/

typedef struct port_args port_args;

void * service_thread(void * ptr_args)
{
	port_args * args = (port_args *)(ptr_args);
	piLock(CUP_KEY);
	short pin_num = args->pin_num;
	short deb_length = args->deb_length;
	short temp = 0;
	//Creates a binary 001, 010, or 100, based on pin number
	short pin_to_data = 1 << (pin_num / 3);
	piUnlock(CUP_KEY);
	//While the thread don't kill bit is high
	while (!(temp & T_KILL))
	{
		//Lock *data for this read
		piLock(CUP_KEY);
		temp = args->data;
		piUnlock(CUP_KEY);
		//If a pin is found and data doesn't already have this pin
		//wait until main clears bit for servicing
		if ( (digitalRead(pin_num) == 0) && !(temp & pin_to_data) )
		{
			//If pin is still being held after debounce
			if ( debounce(pin_num, deb_length, LOW) )
			{
				piLock(CUP_KEY);
				//Assert pin for read from managing thread
				temp = args->data = args->data | pin_to_data;
				
				printf("Cu‎p %d pin has been detected\n", pin_num);
				
				//Servo control
                if ( pin_num == CUP_PIN_1 )
                    pwm_control(136);
                else if ( pin_num == CUP_PIN_2 )
                    pwm_control(154);
                else if ( pin_num == CUP_PIN_3 )
                    pwm_control(173);
				
				piLock(PMP_KEY);
                printf("Locking pump\n");
				PumpControl( args->pump_sel, args->drink_size );
				piUnlock(PMP_KEY);
				printf("Unlocking pump\n");
				
				piUnlock(CUP_KEY);
				sleep(2);//sleep thread for two seconds
                while ( debounce(pin_num, deb_length, LOW) )
                    usleep(50000);
			}
		}
		//Nothing new was found or has already been found
		else
			usleep(500);
	}
	return NULL;
}
