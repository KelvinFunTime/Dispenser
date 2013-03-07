#include "../source/defs.h"
#include <wiringPi.h>
#include "UserButtons.h"
#include <iostream>
//#include <QLabel>
//#include <QString>

using std::cout;
using std::endl;

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

    //QString output;

    cout << "Got to drink size" << endl;

    cout << "\nOz: " << oz << endl;

	while(!done)
	{
		if(digitalRead(USER_PIN_1) == 0)
		{	
			if(oz < 36)
				oz += 1;
            cout << "Oz: " << oz << endl;
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
			if(oz > 1)
				oz -= 1;
            cout << "Oz: " << oz << endl;
			while(digitalRead(USER_PIN_3) == 0);
		}
	}
	
	return oz;
}

int getPump()
{
    int pump = 0;

    while ( !pump )
        if(digitalRead(USER_PIN_1) == 0)
        {
            pump = 2;
            while ( digitalRead(USER_PIN_1) == 0 );
        }
        else if(digitalRead(USER_PIN_3) == 0)
        {
            pump = 1;
            while ( digitalRead(USER_PIN_3) == 0 );
        }

    return pump;
}

