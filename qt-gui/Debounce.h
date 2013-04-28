/*********************************************************************
*	Name:		Debounce
*	Function:	Controls Debounce timing for buttons
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <wiringPi.h>
#include "Defs.h"

int Debounce(int button, int debounce, int direction);

#endif
