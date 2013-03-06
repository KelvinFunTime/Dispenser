#include "defs.h"
#include <wiringPi.h>

void initUserButtons()
{
	pinMode(USER_PIN_1, INPUT);
	pinMode(USER_PIN_2, INPUT);
	pinMode(USER_PIN_3, INPUT);
	
	pullUpDnControl(USER_PIN_1, PUD_UP);
	pullUpDnControl(USER_PIN_2, PUD_UP);
	pullUpDnControl(USER_PIN_3, PUD_UP);
}

int getDrinkSize()
{
	int done = 0;
	int oz = 12;

	while(!done)
	{
		if(digitalRead(USER_PIN_1) == 0)
		{	
			if(oz < 36)
				oz += 1;
			printf("%d", oz);
			while(digitalRead(USER_PIN_1) == 0);
		}
		else if(digitalRead(USER_PIN_2) == 0)
		{
			done = 1;
		}
		else if(digitalRead(USER_PIN_3) == 0)
		{
			if(oz > 1)
				oz -= 1;
			printf("%d", oz);
			while(digitalRead(USER_PIN_3) == 0);
		}
	}
	
	return oz;
}

