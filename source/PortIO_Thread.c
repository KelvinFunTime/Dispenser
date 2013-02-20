#include "PortIO_Thread.h"
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "debounce.h"

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
	pinMode (pin_num, INPUT);
	short temp = T_KILL;
	//Creates a binary 001, 010, or 100, based on pin number
	short pin_to_data = 1 << (pin_num / 3);
	piUnlock(CUP_KEY);
	//While the thread don't kill bit is high
	while (temp & T_KILL)
	{
		//Lock *data for this read
		piLock(CUP_KEY);
		temp = args->data;
		piUnlock(CUP_KEY);
		//If a pin is found and data doesn't already have this pin
		//wait until main clears bit for servicing
		if ( !digitalRead(pin_num) &&  !(temp & pin_to_data) )
			//If pin is still being held after debounce
			if ( debounce(pin_num, deb_length, LOW) );
			{
				piLock(CUP_KEY);
				//Assert pin for read from managing thread
				temp = args->data += pin_to_data;
				
				printf("Cup key has been detected");
				
				//Servo stuff goes here
				
				piLock(PMP_KEY);
				//PumpControl( args->pump_sel, args->drink_size );
				piUnlock(PMP_KEY);
				
				piUnlock(CUP_KEY);
				sleep(2);//sleep thread for two seconds
			}
		//Nothing new was found or has already been found
		//Sleep to free up resources for other threads
	}
}
