#include "Timer.h"

Timer::Timer( QLabel * label, soft_args * args ) {
    m_timer = new QTimer();
    m_label = label;
    m_args = args;
    connect( m_timer, SIGNAL(timeout()), this, SLOT(update_label()) );
    m_timer->setInterval( 10 );
    m_timer->start();
}

void Timer::update_label() {
    static int cup_flag = 0;

    if ( m_args->cup )
    {
        cup_flag = 1;
        m_label->setText( QString("Cup ") + QString::number( m_args->cup ) + QString(" selected") );
    }
    else if ( cup_flag == 1 )
    {
        m_label->setText( QString("Oz: ") + QString::number( m_args->size ) );
    }
    else
        m_label->setText( QString("No cup detected" ) );
}

Timer::~Timer()
{
    delete m_timer;

}
