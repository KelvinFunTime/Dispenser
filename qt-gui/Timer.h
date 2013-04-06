#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <UserButtons.h>

extern "C"
{
#include "../source/HardwareControl.h"
}

class Timer : public QObject {
    Q_OBJECT
public:
    Timer( QLabel * label, soft_args * args );
    ~Timer();
private:
    Timer();
    QTimer * m_timer;
    soft_args * m_args;
    QLabel * m_label;
public slots:
    void update_label();
};

#endif // TIMER_H
