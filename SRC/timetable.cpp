#include "timetable.h"
#include <QDebug>

timetable::timetable(QObject *parent, int ID, int s_hour, int s_min, int inter, int e_hour, int e_min) : QObject(parent)
{
    path_id = ID;
    start_hour = s_hour;
    start_min = s_min;
    interval = inter;
    end_hour = e_hour;
    end_min = e_min;
    if(interval < 1){
        interval = 1;
        qDebug() << "correcting interval";
    }
    if(start_min > 1 && start_hour == 0){
        start_min--;
    }
}
