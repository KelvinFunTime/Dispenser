#include "Defs.h"
#include <wiringPi.h>
#include "UserButtons.h"
#include <iostream>

using std::cout;
using std::endl;

void InitUserButtons()
{
	pinMode(USER_PIN_1, INPUT);
	pinMode(USER_PIN_2, INPUT);
	pinMode(USER_PIN_3, INPUT);
	
	pullUpDnControl(USER_PIN_1, PUD_UP);
	pullUpDnControl(USER_PIN_2, PUD_UP);
	pullUpDnControl(USER_PIN_3, PUD_UP);
}

void getDrinkSize( short & size )
{
	int done = 0;
    size = 12 << 4;

    cout << "\nOz: " << ( size >> 4 ) << endl;

	while(!done)
	{
        usleep(500);
		if(digitalRead(USER_PIN_1) == 0)
		{	
            if( size < 36 << 4 )
                size += 1 << 4;
            cout << "Oz: " << ( size >> 4 ) << endl;
			while(digitalRead(USER_PIN_1) == 0);
		}
		else if(digitalRead(USER_PIN_2) == 0)
		{
			done = 1;
            while(digitalRead(USER_PIN_2) == 0);
            usleep(500000);
		}
		else if(digitalRead(USER_PIN_3) == 0)
		{
            if( size > 1 << 4 )
                size -= 1 << 4;
            cout << "Oz: " << ( size >> 4 ) << endl;
			while(digitalRead(USER_PIN_3) == 0);
		}
	}
}

void getPump(soft_args * args)
{
    while ( !args->pump_num )
        if(digitalRead(USER_PIN_1) == 0)
        {
            args->pump_num = 2;
            while ( digitalRead(USER_PIN_1) == 0 );
        }
        else if(digitalRead(USER_PIN_3) == 0)
        {
            args->pump_num = 1;
            while ( digitalRead(USER_PIN_3) == 0 );
        }
        else
            usleep(500);
}

