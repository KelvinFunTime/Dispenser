#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <iostream>
#include <pthread.h>
#include "UserButtons.h"
#include <QTimer>
#include "Timer.h"
#include <QWidget>
#include <QtGui>
#include "../source/HardwareControl.h"

extern "C"
{
#include "../source/defs.h"
#include <wiringPi.h>
}

using std::cout;
using std::endl;

void * hwControl( void * );
void * enterControl(void *);
void update_label();

soft_args pmp_args;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget main_window;

    QLabel * mw_label = new QLabel( "No cup detected", &main_window) ;

    QVBoxLayout * vbl = new QVBoxLayout( &main_window );

    pthread_t hw_t;
    pmp_args.cup = 0;
    pmp_args.pump_num = 0;
    pmp_args.size = 0;

    pthread_create( &hw_t, NULL, hwControl, NULL);

    vbl->addWidget(mw_label);

    main_window.show();

    Timer timer(mw_label, &pmp_args);

    return app.exec();
}

void * hwControl( void * )
{
    pthread_t cont_t;
    pthread_create( &cont_t, NULL, enterControl, (void *)(&pmp_args) );

    usleep(5000);

    initUserButtons();

    pmp_args.cup = 0;

    while (1)
    {
        piLock(DAT_KEY);
        while ( pmp_args.cup == 0)
            sleep(1);
        pmp_args.cup = 0;
        getDrinkSize(&pmp_args);
        cout << "Select Drink (1 or 2)" << endl;
        getPump(&pmp_args);
        piUnlock(DAT_KEY);
        cout << "Dispensing drink" << endl;
        sleep(5);
        cout << "No cup detected" << endl;

    }
    return 0;
}
