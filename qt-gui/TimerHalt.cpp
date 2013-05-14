#include <wiringPi.h>

#include "TimerHalt.h"
#include "Defs.h"

TimerHalt::TimerHalt() {
    m_timer = new QTimer();
    connect( m_timer, SIGNAL(timeout()), this, SLOT(CheckButton()) );
    m_timer->setInterval( 1000 );
    m_timer->start();
}

void TimerHalt::CheckButton() {
	static bool debounce = false;
    if ( !digitalRead( MURDER_PIN ) )
	{
		if ( debounce )
        {
            if ( !digitalRead( MURDER_PIN ) )
				system("sudo halt");
			else
				debounce = false;
        }
		debounce = true;
	}
}

TimerHalt::~TimerHalt()
{
    delete m_timer;

}
