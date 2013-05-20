#include "TimerLabel.h"

TimerLabel::TimerLabel( QLabel * label, short * args ) {
    m_timer = new QTimer();
    m_label = label;
    m_state = args;
    m_cup = 0;
    connect( m_timer, SIGNAL(timeout()), this, SLOT(UpdateLevel()) );
    m_timer->setInterval( 100 );
    m_timer->start();
}

void TimerLabel::UpdateLevel() {

    QString output = QString("Cup ") + QString::number( m_cup ) + QString(" selected\n");

    if ( (*m_state & SELECT_SIZE) == SELECT_SIZE )
        m_label->setText( output + QString("Number of Oz: ") + QString::number( *m_state >> 4 ) );
    else if ( (*m_state & DONE) == DONE )
        m_label->setText( output + QString("Dispensing drink!") );
    else if ( (*m_state & SELECT_DRINK) == SELECT_DRINK )
        m_label->setText( output + QString("Select Pump 1 or 2") );
    else if ( (*m_state & SELECT_CUP) == SELECT_CUP)
    {
        m_cup = *m_state >> 4;
        output = QString("Cup ") + QString::number( m_cup ) + QString(" selected\n");
        m_label->setText( output );
    }
    else
        m_label->setText( QString("No cup detected") );
}

TimerLabel::~TimerLabel()
{
    delete m_timer;
}
