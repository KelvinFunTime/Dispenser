#include "defs.h"
#include <wiringPi.h>
#include "debounce.h"

/***************************************************************
*Debounce maybe? This is a late game addition.
*
*
****************************************************************/
int debounce (int button, int button_debounce_length, int direction)
{
	int return_value = 0;
	
	usleep (button_debounce_length);
	
	if(digitalRead(button) == direction)
	{
		return_value = 1;
	}
	
	return return_value;
}