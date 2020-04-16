#include "graphic_scene.h"
#include <QGraphicsItem>
#include "custom_line.h"
#include <QMap>
#include <QString>
#include <QDebug>
#include <QTimer>

graphic_scene::graphic_scene(QObject *parent) :
    QGraphicsScene(parent)
{
    st_dict[1] = new custom_line();
    st_dict[1]->setLine(0,0,0,150);
    st_dict[1]->station = 0.3;
    addItem(st_dict[1]);

    st_dict[2] = new custom_line(Qt::blue);
    st_dict[2]->setLine(0,150,200,150);
    addItem(st_dict[2]);

    st_dict[3] = new custom_line(Qt::green);
    st_dict[3]->setLine(200,150,300,300);
    st_dict[3]->station = 0.5;
    addItem(st_dict[3]);

    st_dict[4] = new custom_line(Qt::magenta);
    st_dict[4]->setLine(300,300,500,300);
    st_dict[4]->station = 0.75;
    addItem(st_dict[4]);

    st_dict[5] = new custom_line(Qt::cyan);
    st_dict[5]->setLine(500,300,500,0);
    st_dict[5]->station = 0.1;
    addItem(st_dict[5]);

    st_dict[0] = new custom_line(Qt::blue);
    st_dict[0]->setLine(200,0,0,0);
    st_dict[0]->station = 0.8;
    addItem(st_dict[0]);

    /*
    auto line = new custom_line(Qt::magenta);
    line->setLine(250,0,0,-250);
    addItem(line);
    */

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();

    connect(timer, &QTimer::timeout, this, &graphic_scene::line);
    /*
    qDebug() << st_dict.count();
    foreach (line, st_dict) {
        qDebug() << line->duration << line->m_pen;
    }
    */
}

void graphic_scene::line()
{
    static int active_line = 0;
    static bool forward = true;
    static qreal start = 0.0;
    static qreal end = 1.0;
    static int pause = 500;
    static bool same = false;

    auto line = st_dict[active_line];

    line->anim->setEndValue(end);
    line->anim->setStartValue(start);
    timer->setInterval(line->duration+20);
    line->anim->setDuration(line->duration);

   // qDebug() << start << end << line->duration << same << timer->interval();

    if((line->station != -1) && (same == false)){
        line->anim->setEndValue(line->station);
        timer->setInterval((line->duration*(std::abs(start-line->station)))+pause);
        line->anim->setDuration(line->duration*(std::abs(start-line->station)));
        same = true;
        //qDebug() << line->duration << std::abs(start-line->station) << line->duration*line->station;
        if(forward == true){
            active_line--;
        }else{
            active_line++;
        }

    }else if(same == true){
        line->anim->setStartValue(line->station);
        timer->setInterval((line->duration - (line->duration*(std::abs(start-line->station))))+20);
        line->anim->setDuration(line->duration - (line->duration*(std::abs(start-line->station))));
        same = false;
    }

    //qDebug() << line->anim->duration() << timer->interval();

    //line->active = true;

    line->time_line();

    //qDebug() << active_line;

    if(forward == true){
        active_line++;
    }else{
        active_line--;
    }
    if(active_line == st_dict.count()){
        forward = false;
        active_line--;
        start = 1.0;
        end = 0.0;
        timer->setInterval(timer->remainingTime() + pause);
        qDebug() << timer->remainingTime(); //<< timer->remainingTimeAsDuration();
    }else if(active_line == -1){
        active_line++;
        forward = true;
        start = 0.0;
        end = 1.0;
        timer->setInterval(timer->remainingTime() + pause);
    }

}
