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
	usleep (button_debounce_length);
	
	return (digitalRead(button) == direction);
}