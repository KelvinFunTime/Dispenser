#include "Timer.h"

Timer_Label::Timer_Label( QLabel * label, soft_args * args ) {
    m_timer = new QTimer();
    m_label = label;
    m_args = args;
    connect( m_timer, SIGNAL(timeout()), this, SLOT(update_label()) );
    m_timer->setInterval( 100 );
    m_timer->start();
}

void Timer_Label::update_label() {
    if ( m_args->cup && m_args->size != 0 )
    {
        QString output = QString("Cup ") + QString::number( m_args->cup ) + QString(" selected\n") +
            QString("Number of Oz: ") + QString::number( m_args->size );
        m_label->setText(output);
    }
    else if ( m_args->cup == 0 && m_args->cup != 0)
    {
        m_label->setText( QString("Pump selected: ") + QString::number( m_args->pump_num ) );
    }
    else
        m_label->setText( QString("No cup detected") );
}

Timer_Label::~Timer_Label()
{
    delete m_timer;

}

Timer_Level::Timer_Level() {
    m_timer = new QTimer();
    connect( m_timer, SIGNAL(timeout()), this, SLOT(update_level()) );
    m_timer->setInterval( 60000 );
    m_timer->start();
}

void Timer_Level::update_level() {
    system("python piClient.py 1 Danger");
}

Timer_Level::~Timer_Level()
{
    delete m_timer;

}
