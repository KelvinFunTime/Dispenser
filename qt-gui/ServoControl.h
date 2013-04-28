/*********************************************************************
*	Name:		PWMControl
*	Function:	Controls the servo motors
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <wiringPi.h>

void PWMControl( short pos );

#endif //SERVOCONTROL_H