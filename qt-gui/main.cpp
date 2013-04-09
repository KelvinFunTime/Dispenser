#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <iostream>
#include <pthread.h>
#include "UserButtons.h"
#include <QTimer>
#include "Timer.h"
#include <QWidget>
#include <QtGui>

extern "C"
{
#include "../source/CupSenseT.h"
#include "../source/defs.h"
#include "../source/PortIO_Thread.h"
#include "../source/PumpControllingSystem.h"
#include <wiringPi.h>
}

using std::cout;
using std::endl;

void * hwControl( void * );
void * enterControl(void *);
void initSystem(void);
void initServo(void);
short seperateService( short data );

soft_args pmp_args;

int main(int argc, char *argv[])
{
    cout << "Building application" << endl;

    QApplication app(argc, argv);

    cout << "Building main_window" << endl;

    QWidget main_window;

    cout << "Building label for mw" << endl;

    QLabel * mw_label = new QLabel( "No cup detected", &main_window);
    QFont temp_font( mw_label->font() );
    temp_font.setPointSize( 18 );
    mw_label->setFont( temp_font );
    mw_label->setAlignment( Qt::AlignCenter );

    cout << "Building QVBox" << endl;

    QVBoxLayout * vbl = new QVBoxLayout( &main_window );

    cout << "Spinning up hwControl" << endl;

    pthread_t hw_t;
    pmp_args.cup = 0;
    pmp_args.pump_num = 0;
    pmp_args.size = 0;

    pthread_create( &hw_t, NULL, hwControl, NULL);

    vbl->addWidget(mw_label,0,Qt::Alignment());

    cout << "Starting Timer" << endl;

    Timer_Label timer_label(mw_label, &pmp_args);
    Timer_Level timer_level;

    cout << "Showing main_window" << endl;

    main_window.setFixedHeight(360);
    main_window.setFixedWidth(480);
    main_window.move(QApplication::desktop()->screen()->rect().center() - main_window.rect().center());
    main_window.show();

    cout << "Starting app" << endl;

    return app.exec();
}

void * hwControl( void * )
{
    pthread_t cont_t;

    initSystem();
    initUserButtons();
    initPumpPins();
    initServo();


    pthread_create( &cont_t, NULL, enterControl, (void *)(&pmp_args) );

    usleep(5000);

    pmp_args.cup = 0;

    while (1)
    {
        piLock(DAT_KEY);
        pmp_args.pump_num = 0;
        pmp_args.size = 0;
        while ( pmp_args.cup == 0)
            usleep(500);
        getDrinkSize(&pmp_args);
        pmp_args.cup = 0;
        cout << "Select Drink (1 or 2)" << endl;
        getPump(&pmp_args);
        piUnlock(DAT_KEY);
        cout << "Dispensing drink" << endl;
        sleep(5);
        pmp_args.pump_num = 0;
        pmp_args.size = 0;
        cout << "No cup detected" << endl;
    }
    return 0;
}

void * enterControl( void * s_args)
{
    soft_args * args = (soft_args *)(s_args);
    short cup_data = 0;
    printf("Spinning up threads and preparing cup pins\n");
    init_cup_service();

    printf("Entering service loop\n");

    while(1)
    {
        piLock(PMP_KEY);

        while ( ( cup_data = get_cup_data() ) == 0 )
            usleep(500);

        cup_data = seperateService(cup_data);

        if ( cup_data == DATA_1 )
            args->cup = 1;
        else if ( cup_data == DATA_2 )
            args->cup = 2;
        else if ( cup_data == DATA_3 )
            args->cup = 3;
        printf("HardwareControl found cup %d\n", args->cup);
        piLock(DAT_KEY);
        set_drink_size(args->size);
        set_pump_sel(args->pump_num);
        set_cup_data(0);
        piUnlock(DAT_KEY);
        piUnlock(PMP_KEY);

        usleep(500);
    }
}

void initSystem(void)
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

void initServo(void)
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
