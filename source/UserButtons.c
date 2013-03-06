#include "defs.h"
#include <wiringPi.h>

void initUserButtons()
{
	pinMode(USER_PIN_1, OUTPUT);
	pinMode(USER_PIN_2, OUTPUT);
	pinMode(USER_PIN_3, OUTPUT);
}

