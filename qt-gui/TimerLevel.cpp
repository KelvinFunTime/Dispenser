#include "TimerLevel.h"
#include <wiringPi.h>

TimerLevel::TimerLevel() {
    m_timer = new QTimer();
    connect( m_timer, SIGNAL(timeout()), this, SLOT(update_level()) );
    m_timer->setInterval( 60000 );
    m_timer->start();
}

void TimerLevel::update_level()
{
    int SPICLK = 14;
    int SPIMISO = 13;
    int SPIMOSI = 12;
    int SPICS = 10;
    int i = 0;
    int cmd = 0;
    int input = 0;

    pinMode(SPICLK, 1);
    pinMode(SPIMISO, 0);
    pinMode(SPIMOSI, 1);

    char buffer[2] = {0};
    pinMode(SPICS, 1);

    while(1)
    {
        input = 0;
        cmd = 0x18 << 3;

        digitalWrite(SPICS, 1);
        digitalWrite(SPICLK, 0);
        digitalWrite(SPICS, 0);

        for(i = 0; i < 5; ++i)
        {
            if(cmd & 0x80)
            {
                digitalWrite(SPIMOSI, 1);
            }
            else
            {
                digitalWrite(SPIMOSI, 0);
            }

            cmd = cmd << 1;

            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);
        }

        //Read in
        for(i = 0; i < 12; ++i)
        {
            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);

            input = input << 1;

            if(digitalRead(SPIMISO))
                input = input | 0x1;
        }

        digitalWrite(SPICS, 1);

        input = input >> 1;

        if ( input >= TANK1_HALF )
            system("python pyClient.py 1 FULL");
        else if ( input >= TANK1_QUART )
            system("python pyClient.py 1 HALF");
        else if ( input >= TANK1_EMPTY )
            system("python pyClient.py 1 QUART");
        else
            system("python pyClient.py 1 EMPTY");

        sleep(1);

        input = 0;
        cmd = 0x1F << 3;

        digitalWrite(SPICS, 1);
        digitalWrite(SPICLK, 0);
        digitalWrite(SPICS, 0);

        //Send cmd
        for(i = 0; i < 5; ++i)
        {
            if(cmd & 0x80)
            {
                digitalWrite(SPIMOSI, 1);
            }
            else
            {
                digitalWrite(SPIMOSI, 0);
            }

            cmd = cmd << 1;

            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);
        }

        //Read in
        for(i = 0; i < 12; ++i)
        {
            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);

            input = input << 1;

            if(digitalRead(SPIMISO))
                input = input | 0x1;
        }

        digitalWrite(SPICS, 1);

        input = input >> 1;

        if ( input >= TANK2_HALF )
            system("python pyClient.py 2 FULL");
        else if ( input >= TANK2_QUART )
            system("python pyClient.py 2 HALF");
        else if ( input >= TANK2_EMPTY )
            system("python pyClient.py 2 QUART");
        else
            system("python pyClient.py 2 EMPTY");

        sleep(1);
    }
}

TimerLevel::~TimerLevel()
{

    delete m_timer;

}
