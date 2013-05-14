/*********************************************************************
*	Name:		TimerHalt
*	Function:	Provides a timer specifically for starting a Python
*				script that will relay a message to our server
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef TIMERHALT_H
#define TIMERHALT_H

#include <QObject>
#include <QTimer>
#include <QLabel>

class TimerHalt: public QObject {
    Q_OBJECT
public:
    TimerHalt();
    ~TimerHalt();
private:
    QTimer * m_timer;
public slots:
    void CheckButton();
};

#endif // TIMERHALT_H