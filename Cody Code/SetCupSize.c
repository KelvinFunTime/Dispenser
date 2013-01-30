#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PI_CLOCK 700000000

int SetCupSize (void)
{
	float cup_size = 0;
	
	do 
	{
		printf ("\nPlease Enter Your Cup Size (in ounces): ");		// Prompts user for cup size in oz
		scanf ("%f", &cup_size);										// gets user input for cup size
	}	while (cup_size < 0 && cup_size > 34);						// wont exit until valid cup size
	
	cup_size = (cup_size * 1.2);									// 1.2 seconds for each ounce
	cup_size = (int)((cup_size * PI_CLOCK)/10.5);	
										// this gives correct timing per ounce
	return (cup_size);								// creates correct value for loop
}																	// according to cup size determined
