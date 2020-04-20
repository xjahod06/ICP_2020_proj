#include "clock.h"
#include <QLCDNumber>
#include <QTimer>
#include <QString>
#include <QDebug>

clock::clock(QWidget *parent) :
    QLCDNumber(parent)
{
    resize(150,60);
    display("00:00");
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &clock::time_up);
    timer->start();
}

void clock::speed_change(int val)
{
    speed = abs(val-25)/15.0;
    qDebug() << "clock speed" << speed << abs(val-25);
    timer->setInterval(1000*speed);
}

void clock::reset_time()
{
    timer->stop();
    minute = 0;
    hour = 0;
    timer->start();
}

QString clock::convert_time(int min, int hour)
{
    min_string.setNum(min);
    hour_string.setNum(hour);

    QString final_text;

    if(hour < 10){
        final_text += "0";
    }
    final_text += hour_string+separator;

    if(min < 10){
        final_text += "0";
    }
    final_text += min_string;

    return final_text;
}

void clock::time_up()
{
    minute++;
    if(minute == 60){
        hour++;
        minute = 0;
    }

    display(convert_time(minute,hour));
    emit propagade_clock(hour,minute);


}
