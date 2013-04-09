#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <UserButtons.h>

class Timer_Label : public QObject {
    Q_OBJECT
public:
    Timer_Label( QLabel * label, soft_args * args );
    ~Timer_Label();
private:
    Timer_Label();
    QTimer * m_timer;
    soft_args * m_args;
    QLabel * m_label;
public slots:
    void update_label();
};

class Timer_Level: public QObject {
    Q_OBJECT
public:
    Timer_Level();
    ~Timer_Level();
private:
    QTimer * m_timer;
public slots:
    void update_level();
};

#endif // TIMER_H
