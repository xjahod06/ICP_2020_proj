#include "graphic_scene.h"
#include "custom_line.h"
#include "path.h"
#include <QGraphicsItem>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QTimer>

graphic_scene::graphic_scene(QObject *parent) :
    QGraphicsScene(parent)
{
    st_dict[1] = new custom_line(Qt::magenta);
    st_dict[1]->setLine(0,0,0,150);
    st_dict[1]->station = 0.8;
    addItem(st_dict[1]);

    st_dict[2] = new custom_line(Qt::magenta);
    st_dict[2]->setLine(0,150,200,150);
    addItem(st_dict[2]);

    st_dict[3] = new custom_line(Qt::magenta);
    st_dict[3]->setLine(200,150,300,300);
    st_dict[3]->station = 0.5;
    addItem(st_dict[3]);

    st_dict[4] = new custom_line(Qt::magenta);
    st_dict[4]->setLine(300,300,500,300);
    st_dict[4]->station = 0.75;
    addItem(st_dict[4]);

    st_dict[5] = new custom_line(Qt::magenta);
    st_dict[5]->setLine(500,300,500,0);
    st_dict[5]->station = 0.35;
    addItem(st_dict[5]);

    st_dict[0] = new custom_line(Qt::magenta);
    st_dict[0]->setLine(200,0,0,0);
    st_dict[0]->station = 0.8;
    addItem(st_dict[0]);

    vehicle_dict[0] = new vehicle();
    vehicle_dict[0]->m_pen = QPen({Qt::blue},3);
    vehicle_dict[1] = new vehicle();
    vehicle_dict[1]->m_pen = QPen({Qt::red},3);

    path_dict[0] = new path();
    path_dict[0]->st_dict[0] = st_dict[0];
    path_dict[0]->st_dict[1] = st_dict[1];
    path_dict[0]->st_dict[2] = st_dict[2];
    path_dict[0]->st_dict[3] = st_dict[3];
    path_dict[0]->a = 100;
    path_dict[0]->m_vehicle = vehicle_dict[0];

    path_dict[1] = new path();
    path_dict[1]->st_dict[0] = st_dict[4];
    path_dict[1]->st_dict[1] = st_dict[5];
    path_dict[1]->m_vehicle = vehicle_dict[1];

    /*
    for (int i = 0 ; i < vehicle_dict.count(); i++) {
        for (int j = 0 ; j < st_dict.count(); j++) {
            st_dict[j]->vehicle_dict[i] = vehicle_dict[i];
            st_dict[j]->time_line(i);
        }
    }
    */
    qDebug() << &(path_dict[0]->m_vehicle) << &(vehicle_dict[0]);

    //path_dict[0]->timer->start();
    //path_dict[1]->timer->start();

    /*
    path_dict[0]->m_vehicle->anim->setDuration(3000);
    path_dict[0]->m_vehicle->active = true;
    path_dict[0]->m_vehicle->anim->setStartValue(0.0);
    path_dict[0]->m_vehicle->anim->setEndValue(1.0);
    path_dict[0]->m_vehicle->anim->start();
    */


    /*
    auto line = new custom_line(Qt::magenta);
    line->setLine(250,0,0,-250);
    addItem(line);
    */
    /*
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();

    connect(timer, &QTimer::timeout, this, &graphic_scene::line);
    */
    /*
    qDebug() << st_dict.count();
    foreach (line, st_dict) {
        qDebug() << line->duration << line->m_pen;
    }
    */
}

void graphic_scene::speed_change(int val)
{
    speed = abs(val-25)/15.0;
    qDebug() << "speed" <<speed;
    foreach (auto path, path_dict) {
       path->speed = speed;
    }
}
