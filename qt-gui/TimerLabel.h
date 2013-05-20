/*********************************************************************
*	Name:		TimerLabel
*	Function:	Provides a timer for updating the GUI at regular
*				times.
*
*	Author:		Wesley Maxey, Kelvin McDonald
*********************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <UserButtons.h>
#include "Defs.h"

class TimerLabel : public QObject {
    Q_OBJECT
public:
    TimerLabel( QLabel * label, short * state );
    ~TimerLabel();
private:
    TimerLabel();
    QTimer * m_timer;
    short * m_state;
    QLabel * m_label;
    short m_cup;
public slots:
    void UpdateLevel();
};

#endif // TIMER_H
