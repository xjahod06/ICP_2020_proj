/** ICP Project 2020 transport map
 * @file clock.cpp
 * @brief object na řízení hodin programu
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */

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
    foreach (auto table, timetables) {
        table->active = false;
    }
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

void clock::add_timetable(int ID, int start_hour, int start_min, int end_hour, int end_min, int interval)
{
    timetables[timetables.count()] = new timetable(this,ID,start_hour,start_min,interval,end_hour,end_min);

}

void clock::reset_timetables()
{
    timetables.clear();
    reset_time();
}
void clock::check_the_start_timetables()
{
    timer->start();
    foreach (auto table, timetables) {
        if(table->start_hour == hour && table->start_min == minute && table->active == false){
            emit start_new_line(table->path_id,minute,hour);
            table->active = true;
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
            if(((hour*60+minute) - (table->start_hour*60 + table->start_min)) != 0){
                if(((hour*60+minute) - (table->start_hour*60 + table->start_min)) % table->interval == 0){
                    emit start_new_line(table->path_id,minute,hour);
                }
            }
        }
    }


}
