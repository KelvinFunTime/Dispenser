#include <QtGui/QApplication>
#include <QTextStream>
#include "qmlapplicationviewer.h"
#include <iostream>
#include <pthread.h>

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
    QApplication app(argc, argv);
    QmlApplicationViewer viewer;

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/qtgui/main.qml"));
    viewer.showExpanded();

    cout << "Spinning up thread for hardware controller\n";
    pthread_t cont_t;
    pthread_t gui_t;

    soft_args t_args;
    pthread_create( &cont_t, NULL, enterControl, (void *)(&t_args) );

    pthread_create( &gui_t, NULL, &app.exec, NULL );

    while (1)
    {
        piLock(DAT_KEY);

    }
    return 0;
}
