#include "TimerLevel.h"

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

    char buffer[2] = {0};

    if(wiringPiSetup() == -1)
    {
        printf("Ohhhhhhhhhhhhhh\n");
    }

    pinMode(SPICLK, 1);
    pinMode(SPIMISO, 0);
    pinMode(SPIMOSI, 1);
    pinMode(SPICS, 1);

    while(1)
    {
        printf("\nIn 1\n");
        input = 0;
        cmd = 0x18 << 3;

        digitalWrite(SPICS, 1);
        digitalWrite(SPICLK, 0);
        digitalWrite(SPICS, 0);

        printf("Cmd sent: ");
        //Send cmd
        for(i = 0; i < 5; ++i)
        {
            if(cmd & 0x80)
            {
                printf("1");
                digitalWrite(SPIMOSI, 1);
            }
            else
            {
                printf("0");
                digitalWrite(SPIMOSI, 0);
            }

            cmd = cmd << 1;

            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);
        }

        printf("\n");

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

        printf("Output: %X\n", input);

        sleep(1);

        printf("\nIn 2\n");
        input = 0;
        cmd = 0x1F << 3;

        digitalWrite(SPICS, 1);
        digitalWrite(SPICLK, 0);
        digitalWrite(SPICS, 0);

        printf("Cmd sent: ");
        //Send cmd
        for(i = 0; i < 5; ++i)
        {
            if(cmd & 0x80)
            {
                printf("1");
                digitalWrite(SPIMOSI, 1);
            }
            else
            {
                printf("0");
                digitalWrite(SPIMOSI, 0);
            }

            cmd = cmd << 1;

            digitalWrite(SPICLK, 1);
            digitalWrite(SPICLK, 0);
        }

        printf("\n");

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

        printf("Output: %X\n", input);

        sleep(1);
    }

    return 0;
}

TimerLevel::~TimerLevel()
{

    delete m_timer;

}
