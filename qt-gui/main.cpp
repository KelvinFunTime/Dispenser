//#include <QtGui/QApplication>
//#include <QTextStream>
//#include "qmlapplicationviewer.h"
#include <iostream>
#include <pthread.h>
//#include <QLabel>
#include "UserButtons.h"

extern "C"
{
#include "../source/HardwareControl.h"
#include "../source/defs.h"
#include <wiringPi.h>
}

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
//    QmlApplicationViewer viewer;

//    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.setMainQmlFile(QLatin1String("qml/qtgui/main.qml"));
//    viewer.showExpanded();

//    app.exec();
//    cout << "Spinning up thread for hardware controller\n";
    pthread_t cont_t;
//    pthread_t gui_t;

//    QLabel * label = new QLabel("No cup detected");

    soft_args pmp_args;

//    label->show();

    cout << "What's going on?" << endl;

    pthread_create( &cont_t, NULL, enterControl, (void *)(&pmp_args) );

    usleep(5000);

    initUserButtons();

    pmp_args.cup = 0;

    cout << "Do I get here?" << endl;

    while (1)
    {
        piLock(DAT_KEY);
        while ( pmp_args.cup == 0)
            sleep(1);
        pmp_args.cup = 0;
        cout << "Got to drink!" << endl;
        pmp_args.size = getDrinkSize();
        cout << "Select Drink (1 or 2)" << endl;
        pmp_args.pump_num = getPump();
        piUnlock(DAT_KEY);
        cout << "Dispensing drink" << endl;
        sleep(5);
        cout << "No cup detected" << endl;

    }
    return 0;
}
