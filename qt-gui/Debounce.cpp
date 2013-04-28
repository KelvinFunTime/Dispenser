#include "Defs.h"
#include <wiringPi.h>
#include "Debounce.h"
#include "unistd.h"

int Debounce (int button, int debounce, int direction)
{	
    usleep (debounce);
	return (digitalRead(button) == direction);
}
