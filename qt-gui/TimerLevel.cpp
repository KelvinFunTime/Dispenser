#include "TimerLevel.h"

TimerLevel::TimerLevel() {
    m_timer = new QTimer();
    connect( m_timer, SIGNAL(timeout()), this, SLOT(update_level()) );
    m_timer->setInterval( 60000 );
    m_timer->start();
}

void TimerLevel::update_level() {
    system("python piClient.py 1 Full");
    system("python piClient.py 2 Half");
}

TimerLevel::~TimerLevel()
{
    delete m_timer;

}
