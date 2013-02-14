/***************************************************************
*Purpose:
*	Contains thread used for portio.
*
*Inputs:
*	Receives commands from main_thread (pwm, pin number, etc)
*
*Outputs:
*	Sends out IO through the pins and can clear commands from
*	main_thread
*
****************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "debounce.c"
#include "PortIO_Thread.h"

//Sets compatability for pthread
#define pin_num 	Args.pin_num
#define deb_length 	Args.deb_length
#define data 		Args.data
#define drink_size 	Args.drink_size
#define pump_sel 	Args.pump_sel

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

void service_thread(port_args Args)
{
	pinMode (pin_num, INPUT);
	short temp = T_KILL;
	//Creates a binary 001, 010, or 100, based on pin number
	short pin_to_data = 1 << (pin_num / 3);
	
	//While the thread don't kill bit is high
	while (temp & T_KILL)
	{
		//Lock *data for this read
		piLock(CUP_KEY);
		temp = *data;
		piUnlock(CUP_KEY);
		//If a pin is found and data doesn't already have this pin
		//wait until main clears bit for servicing
		if ( !digitalRead(pin_num) &&  !(temp & pin_to_data) )
			//If pin is still being held after debounce
			if ( debounce(pin_num, deb_length, LOW) );
			{
				piLock(CUP_KEY);
				//Assert pin for read from managing thread
				temp = *data += pin_to_data;
				
				//Servo stuff goes here
				
				piLock(PMP_KEY);
				PumpControl( *pump_sel, *drink_size );
				piUnlock(PMP_KEY);
				
				piUnlock(CUP_KEY);
				sleep(2);//sleep thread for two seconds
			}
		//Nothing new was found or has already been found
		//Sleep to free up resources for other threads
	}
}

