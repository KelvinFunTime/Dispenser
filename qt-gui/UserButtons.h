/*********************************************************************
*	Name:		UserButtons
*	Function:	Provides input interfaces for the buttons on top of
*				our dispenser
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef USER_BUTTS_H
#define USER_BUTTS_H

#include "Defs.h"

void InitUserButtons();
void getDrinkSize( short & );
void getPump(soft_args *);

#endif
