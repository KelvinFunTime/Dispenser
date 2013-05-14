/*********************************************************************
*	Name:		CupButtons
*	Function:	Controls the buttons responsible for driving the cups
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef CUPBUTTON_H
#define CUPBUTTON_H

#include <pthread.h>

class CupButtons
{
private:
    pthread_t m_cup_t1;
    pthread_t m_cup_t2;
    pthread_t m_cup_t3;
	
	bool  m_cup1;
	bool  m_cup2;
	bool  m_cup3;
	short m_deb_length;
	short m_args;
	int   m_pump_sel;
	int   m_drink_size;
	
public:
	CupButtons();
	~CupButtons();
	
	void KillThread( int thread_num );
	short GetButtons();
    static void * ThreadWrapper( void * );
    void CupThread( int );
    void ClearButton( short button );
	void SetDrinkSize( short size );
	void SetPumpSelect( short pump );
};

#endif
