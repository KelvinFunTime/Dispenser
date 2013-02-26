#include <QtGui/QApplication>
#include <QTextStream>
#include "qmlapplicationviewer.h"
#include <iostream>
#include <pthread.h>

extern "C"
{
#include "../source/HardwareControl.h"
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
    pthread_t t;
    soft_args t_args;
    pthread_create( &t, NULL, enterControl, (void *)(&t_args) );

    app.exec();

    return 0;
}
