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
    static short prev_cup = 0;
    QString output = QString("Cup ") + QString::number( m_args->cup ) + QString(" selected\n");
    if ( m_args->cup && m_args->size != 0 )
    { 
        prev_cup = m_args->cup;
        m_label->setText(output + QString("Number of Oz: ") + QString::number( m_args->size ) );
    }
    else if ( m_args->pump_num )
    {
        output = QString("Cup ") + QString::number( prev_cup ) + QString(" selected\n");
        m_label->setText( output + QString("Dispensing drink!") );
    }
    else if ( m_args->cup == 0 && m_args->size != 0)
    {
        output = QString("Cup ") + QString::number( prev_cup ) + QString(" selected\n");
        m_label->setText( output + QString("Select Pump 1 or 2") );
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
    system("python piClient.py 1 Full");
    system("python piClient.py 2 Half");
}

Timer_Level::~Timer_Level()
{
    delete m_timer;

}
