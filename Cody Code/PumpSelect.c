#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int PumpSelect (void)
{
	int pump = 0;
	
	do 
	{
		printf ("\nPlease Enter 1 for Pump 1, or 2 for Pump 2: ");
		
		scanf ("%d", &pump);
	} while (pump != 1 && pump != 2);
	
	return pump;
}