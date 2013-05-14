/*********************************************************************
*	Name:		TimerLevel
*	Function:	Provides a timer specifically for starting a Python
*				script that will relay a message to our server
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef TIMERLEVEL_H
#define TIMERLEVEL_H

#include <QObject>
#include <QTimer>
#include <QLabel>

#include "Defs.h"

class TimerLevel: public QObject {
    Q_OBJECT
public:
    TimerLevel();
    ~TimerLevel();
private:
    QTimer * m_timer;
public slots:
    void update_level();
};

#endif // TIMERLEVEL_H
