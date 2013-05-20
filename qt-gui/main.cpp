#include <QtGui/QApplication>
#include <QWidget>
#include <QtGui>
#include <QTimer>
#include <iostream>
#include <pthread.h>
#include <wiringPi.h>

#include "qmlapplicationviewer.h"
#include "UserButtons.h"
#include "CupButtons.h"
#include "TimerLevel.h"
#include "TimerLabel.h"
#include "TimerHalt.h"
#include "PumpControl.h"

using std::cout;
using std::endl;

void * hwControl( void * );
void InitSystem(void);
void InitServo(void);
short seperateService( short data );

soft_args pmp_args;
short state;

int main(int argc, char *argv[])
{
    InitSystem();

    cout << "Building application" << endl;

    QApplication app(argc, argv);

    cout << "Building main_window" << endl;

    QWidget main_window;

    cout << "Showing main_window" << endl;

    main_window.setFixedHeight(360);
    main_window.setFixedWidth(480);
    main_window.move(QApplication::desktop()->screen()->rect().center() - main_window.rect().center());
    main_window.show();
    main_window.showFullScreen();

    cout << "Building label for mw" << endl;

    QLabel * mw_label = new QLabel( "No cup detected", &main_window);
    QFont temp_font( mw_label->font() );
    temp_font.setPointSize( 18 );
    mw_label->setFont( temp_font );
    mw_label->setAlignment( Qt::AlignCenter );

    cout << "Building QVBox" << endl;

    QVBoxLayout * vbl = new QVBoxLayout( &main_window );
    vbl->addWidget( mw_label, 0, Qt::Alignment());

    cout << "Spinning up hwControl" << endl;

    pthread_t hw_t;
    pmp_args.cup = 0;
    pmp_args.pump_num = 0;
    pmp_args.size = 0;

    pthread_create( &hw_t, NULL, hwControl, NULL);

    cout << "Starting Timer" << endl;

    TimerLabel timerLabel(mw_label, &state);
    TimerLevel timerLevel;
    TimerHalt  timerHalt;

    cout << "Starting app" << endl;

    return app.exec();
}

void * hwControl( void * )
{
    InitSystem();
    InitUserButtons();
    InitPumpPins();
    InitServo();
    short cup_data;
    CupButtons cb;

    usleep(5000);

    pmp_args.cup = 0;

    while (1)
    {
        pmp_args.pump_num = 0;
        pmp_args.size = 0;
		
        state = IDLE;
		//Prepare data for pump
		piLock(PMP_KEY);

        while ( !( cup_data = cb.GetButtons() ) )
            usleep(500);

		cup_data = seperateService(cup_data);

        state = SELECT_CUP;

		if ( cup_data == DATA_1 )
            pmp_args.cup = 1;
        else if ( cup_data == DATA_2 )
            pmp_args.cup = 2;
        else if ( cup_data == DATA_3 )
            pmp_args.cup = 3;

        state = pmp_args.cup << 4;

        sleep(1);
		
        state = SELECT_SIZE;
        getDrinkSize( state );
        cb.SetDrinkSize( pmp_args.size );

        state = SELECT_DRINK;
		getPump(&pmp_args);
		cb.SetPumpSelect( pmp_args.pump_num );

        state = DONE;

        cb.ClearButton( cup_data );
        pmp_args.cup = 0;

		piUnlock(PMP_KEY);
        sleep(5);
    }
    return NULL;
}

void InitSystem(void)
{
    printf("Checking wiringPi setup\n");
    int setupCheck = wiringPiSetup();	// WiringPi init

    while(setupCheck == -1)
    {
        // If you're stuck here, wiringPi failed to init
    }

    setupCheck = piHiPri(99);
    printf("Second while loop\n");
    while(setupCheck == -1)
    {
        // If you're stuck here, the Pi failed to be elevated to highest priority
    }
    printf("Set up finished\n");
}

void InitServo(void)
{
    system("gpio mode 1 pwm");
    usleep(500);
    system("gpio pwm-ms");
    usleep(500);
    system("gpio pwmc 200");
    usleep(500);
    system("gpio pwm 1 103");
    usleep(1500000);
    system("gpio pwm 1 0");
}

short seperateService( short data )
{
    if ( data & 0b001 )
        data = 0b001;
    else if ( data & 0b010 )
        data = 0b010;
    else if ( data & 0b100 )
        data = 0b100;
    return data;
}
