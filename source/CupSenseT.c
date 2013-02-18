#include "CupSenseT.h"

void init_cup_pins( pthread_t * t)
{
	//Set static pointers for thread stuff
	
	//Create cup pin arguments for thread
	cup_args.data = 0b0000;
	cup_args.deb_length = CUP_SENSE_DEBOUNCE_LENGTH;
	cup_args.drink_size = 0;
	cup_args.pump_sel = 0;
	
	
	cup_args.pin_num = CUP_PIN_1;	
	pthread_create(t[0], NULL, port_input, &cup_args);
	cup_args.pin_num = CUP_PIN_2;
	pthread_create(t[1], NULL, port_input, &cup_args);
	cup_args.pin_num = CUP_PIN_3;
	pthread_create(t[2], NULL, port_input, &cup_args);
}

/***************************************************************
*Name: 
*	cup_sense
*Inputs:
*	cup_data, cup bits for what is currently active (active high)
*	drink_size, value for how long to drive motor
*	pump_select, selects a pump to drive
*Outputs:
*	returns an int referring to true or false
****************************************************************/

void init_cup_service()
{
	static pthread_t t[3];
	int temp = 0;
	
	if ( t[0] )
		init_cup_pins(t, cup_data, drink_size, pump_sel);
}

void set_cup_data( short cup_data )
{
	cup_args.cup_data = cup_data;
}

void set_drink_size( short drink_size )
{
	cup_args.drink_size = drink_size;
}

void set_pump_sel( short pump_sel )
{
	cup_args.pump_sel = pump_sel;
}

short get_cup_data()
{
	return cup_args.cup_data;
}
