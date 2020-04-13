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
    addItem(st_dict[1]);

    st_dict[2] = new custom_line(Qt::blue);
    st_dict[2]->setLine(0,150,150,150);
    addItem(st_dict[2]);

    st_dict[3] = new custom_line(Qt::green);
    st_dict[3]->setLine(150,150,150,0);
    addItem(st_dict[3]);

    st_dict[0] = new custom_line(Qt::blue);
    st_dict[0]->setLine(150,0,0,0);
    addItem(st_dict[0]);

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();

    connect(timer, &QTimer::timeout, this, &graphic_scene::line);

    qDebug() << st_dict.count();

}

void graphic_scene::line()
{
    static int active_line = 0;
    static bool forward = true;
    static int start = 0;
    timer->setInterval(st_dict[active_line]->duration+100);

    st_dict[active_line]->start_anim = start;
    st_dict[active_line]->active = true;
    st_dict[active_line]->time_line();

    if(forward == true){
        active_line++;
    }else{
        active_line--;
    }
    //qDebug() << active_line;
    if(active_line == st_dict.count()){
        forward = false;
        active_line--;
        start = 1;
    }else if(active_line == -1){
        active_line++;
        forward = true;
        start = 0;
    }

}
