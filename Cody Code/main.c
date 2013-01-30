#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PumpSelect.c"
#include "SetCupSize.c"
#include "PumpControl.c"

int PumpSelect (void);
int SetCupSize (void);
int PumpControl (int pump_select, int time_interval);

int main ()
{
	int interval = 0;
	int pump = 0;
	
	if (wiringPiSetup () == -1)
		exit (1);
		
	// wiringPi Pin 7, Pin 7 on Board 
	pinMode (7, INPUT); 												

	// makes pin 7 active high 
	pullUpDnControl (7, PUD_UP); 	

	// wiringPi Pin 2, Pin 13 on Board
	pinMode (2, OUTPUT); 												

	// wiringPi Pin 0, Pin 11 on Board
	pinMode (0 , OUTPUT);
	
	while (1)
	{
		pump = PumpSelect ();

		interval = SetCupSize ();

		PumpControl (pump, interval);
		
		printf ("\nThank You, Come Again!\n");
	}
	
	
	return 0;
}

