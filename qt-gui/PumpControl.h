/*********************************************************************
*	Name:		PumpControl
*	Functions:	Controls the pump hardware and initialization
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef PUMPCONTROL_H
#define PUMPCONTROL_H

int	PumpControl(int pump_select, int time_interval);
void InitPumpPins();

#endif