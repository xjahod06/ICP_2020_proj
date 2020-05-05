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
    //timer->start();
    add_timetable(0,0,0,5,0,15);
    add_timetable(1,0,1,5,0,20);
    add_timetable(2,0,2,5,0,25);
    add_timetable(1,2,0,10,3,0);
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
    display("00:00");
    timer->setInterval(1000);
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

void clock::add_timetable(int ID, int start_hour, int start_min, int interval, int end_hour, int end_min)
{
    timetables[timetables.count()] = new timetable(this,ID,start_hour,start_min,interval,end_hour,end_min);
}

void clock::check_the_start_timetables()
{
    foreach (auto table, timetables) {
        if(table->start_hour == hour && table->start_min == minute && table->active == false){
            emit start_new_line(table->path_id,minute,hour);
            table->active = true;
            continue;
        }
    }
}

void clock::toggle_timer()
{
    timer->isActive() == true ? timer->stop() : timer->start();
}

void clock::time_up()
{
    minute++;
    if(minute == 60){
        hour++;
        minute = 0;
    }
    /*
    if(minute % 10 == 0){
        emit start_new_line(rand()%3,minute,hour);
    }*/
    display(convert_time(minute,hour));
    emit propagade_clock(hour,minute);
    foreach (auto table, timetables) {
        if(table->start_hour == hour && table->start_min == minute && table->active == false){
            emit start_new_line(table->path_id,minute,hour);
            table->active = true;
            continue;
        }
        if(table->end_hour == hour && table->end_min == minute && table->active == true){
            table->active = false;
            continue;
        }
        if(table->active == true){
            if((minute - table->start_min) % table->interval == 0){
                emit start_new_line(table->path_id,minute,hour);
            }
        }
    }

}
