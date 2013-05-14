#include "CupButtons.h"
#include "Defs.h"
#include "Debounce.h"
#include "ServoControl.h"
#include "PumpControl.h"

extern "C"
{
#include <wiringPi.h>
}
#include <unistd.h>
#include <pthread.h>

CupButtons::CupButtons()
{
	//Set the thread handles to null
    m_cup_t1 = 0;
    m_cup_t2 = 0;
    m_cup_t3 = 0;

    m_cup1 = 0;
    m_cup2 = 0;
    m_cup3 = 0;
	
	//Init Pump Pins
    InitPumpPins();
	
    //Init cup pins
    pinMode(CUP_PIN_1, INPUT);
	pullUpDnControl(CUP_PIN_1, PUD_UP);

	pinMode(CUP_PIN_2, INPUT);
	pullUpDnControl(CUP_PIN_2, PUD_UP);

	pinMode(CUP_PIN_3, INPUT);
    pullUpDnControl(CUP_PIN_3, PUD_UP);

	//Start worker threads through a static function call
    pthread_create( &m_cup_t3, NULL, ThreadWrapper, (void *)(this) );
	usleep(50);
    pthread_create( &m_cup_t2, NULL, ThreadWrapper, (void *)(this) );
	usleep(50);
    pthread_create( &m_cup_t1, NULL, ThreadWrapper, (void *)(this) );
	usleep(50);
}

short CupButtons::GetButtons()
{
    short temp = ( m_cup1 )
               + ( m_cup2 << 1 )
               + ( m_cup3 << 2 );
	
	return temp;
}

void CupButtons::SetDrinkSize( short size )
{
	m_drink_size = size;
}

void CupButtons::SetPumpSelect( short pump )
{
	m_pump_sel = pump;
}

void CupButtons::ClearButton( short button )
{
	if ( button & 0b0001 )
        m_cup1 = 0;
	else if ( button & 0b0010 )
        m_cup2 = 0;
	else if ( button & 0b0100 )
        m_cup3 = 0;
}

void * CupButtons::ThreadWrapper( void * o )
{
    CupButtons * t = (CupButtons *)(o);
    if ( t->m_cup_t1 )
        t->CupThread( CUP_PIN_1 );
    else if ( t->m_cup_t2 )
        t->CupThread( CUP_PIN_2 );
    else if ( t->m_cup_t3 )
        t->CupThread( CUP_PIN_3 );
}

CupButtons::~CupButtons()
{
	//Implement pthread_cancel here to kill threads properly
}

void CupButtons::CupThread( int arg )
{
    int pin_num = arg;

	while ( 1 )
    {
        usleep(500);
		if ( digitalRead(pin_num) == 0 )
		{
			//If pin is still being held after debounce
            if ( Debounce( pin_num, CUP_SENSE_DEBOUNCE_LENGTH, LOW ) )
			{
				//Lock the cup keys for control
				piLock(CUP_KEY);
				
				//Assert pin for read from managing thread
				switch (pin_num)
				{
				case CUP_PIN_1:
                    m_cup1 = 1;
					PWMControl(119);
					break;
				case CUP_PIN_2:
                    m_cup2 = 1;
					PWMControl(103);
					break;
				case CUP_PIN_3:
                    m_cup3 = 1;
					PWMControl(84);
					break;
				}

				//Lock the pump for control
				piLock(PMP_KEY);
				
				//Send out Pump controls
                PumpControl( m_pump_sel, m_drink_size );
                sleep(2);
				
				//Unlock stuff for other threads
				piUnlock(PMP_KEY);
				piUnlock(CUP_KEY);
				
				//sleep thread for two seconds
				sleep(2);
				//Sleep thread until the button is released
                while ( Debounce(pin_num, CUP_SENSE_DEBOUNCE_LENGTH, LOW) )
                    usleep(50000);
			}
		}
	}

}
