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
    st_dict[0] = new custom_line(def_road_color);
    st_dict[0]->setLine(200,-50,0,0);
    st_dict[0]->station = 0.8;
    addItem(st_dict[0]);

    st_dict[1] = new custom_line(def_road_color);
    st_dict[1]->setLine(0,0,0,150);
    st_dict[1]->station = 0.8;
    addItem(st_dict[1]);

    st_dict[2] = new custom_line(def_road_color);
    st_dict[2]->setLine(0,150,200,150);
    addItem(st_dict[2]);

    st_dict[3] = new custom_line(def_road_color);
    st_dict[3]->setLine(300,300,200,150);
    st_dict[3]->station = 0.5;
    addItem(st_dict[3]);

    st_dict[4] = new custom_line(def_road_color);
    st_dict[4]->setLine(500,300,300,300);
    st_dict[4]->station = 0.75;
    addItem(st_dict[4]);

    st_dict[5] = new custom_line(def_road_color);
    st_dict[5]->setLine(500,0,500,300);
    st_dict[5]->station = 0.35;
    addItem(st_dict[5]);

    st_dict[6] = new custom_line(def_road_color);
    st_dict[6]->setLine(200,-50,200,150);
    st_dict[6]->station = 0.1;
    addItem(st_dict[6]);

    st_dict[7] = new custom_line(def_road_color);
    st_dict[7]->setLine(300,300,0,300);
    st_dict[7]->station = 0.45;
    addItem(st_dict[7]);

    st_dict[8] = new custom_line(def_road_color);
    st_dict[8]->setLine(200,-50,500,0);
    st_dict[8]->station = 0.2;
    addItem(st_dict[8]);

    vehicle_dict[0] = new vehicle();
    vehicle_dict[0]->setPen(QPen({Qt::blue},3));
    vehicle_dict[0]->pos_in_dict = 0;
    vehicle_dict[0]->setRect(0,0,0,0);
    addItem(vehicle_dict[0]);
    connect(vehicle_dict[0], &vehicle::circle_clicked, this, &graphic_scene::check_clicked);

    vehicle_dict[1] = new vehicle();
    vehicle_dict[1]->setPen(QPen({Qt::red},3));
    vehicle_dict[1]->pos_in_dict = 1;
    vehicle_dict[1]->setRect(0,0,0,0);
    addItem(vehicle_dict[1]);
    connect(vehicle_dict[1], &vehicle::circle_clicked, this, &graphic_scene::check_clicked);

    vehicle_dict[2] = new vehicle();
    vehicle_dict[2]->setPen(QPen({Qt::green},3));
    vehicle_dict[2]->pos_in_dict = 2;
    vehicle_dict[2]->setRect(0,0,0,0);
    addItem(vehicle_dict[2]);
    connect(vehicle_dict[2], &vehicle::circle_clicked, this, &graphic_scene::check_clicked);

    path_dict[0] = new path(this);
    path_dict[0]->st_dict[0] = st_dict[0];
    path_dict[0]->st_dict[1] = st_dict[1];
    path_dict[0]->st_dict[2] = st_dict[2];
    path_dict[0]->st_dict[3] = st_dict[3];
    path_dict[0]->st_dict[4] = st_dict[7];
    path_dict[0]->find_corr_way();
    path_dict[0]->m_vehicle = vehicle_dict[0];

    path_dict[1] = new path(this);
    path_dict[1]->st_dict[0] = st_dict[3];
    path_dict[1]->st_dict[1] = st_dict[4];
    path_dict[1]->st_dict[2] = st_dict[5];
    path_dict[1]->st_dict[3] = st_dict[8];
    path_dict[1]->find_corr_way();
    path_dict[1]->m_vehicle = vehicle_dict[1];

    path_dict[2] = new path(this);
    path_dict[2]->st_dict[0] = st_dict[6];
    path_dict[2]->st_dict[1] = st_dict[3];
    path_dict[2]->st_dict[2] = st_dict[7];
    path_dict[2]->find_corr_way();
    path_dict[2]->m_vehicle = vehicle_dict[2];

    path_dict[0]->timer->start();
    path_dict[1]->timer->start();
    path_dict[2]->timer->start();

}

void graphic_scene::speed_change(int val)
{
    speed = abs(val-25)/15.0;
    qDebug() << "speed" << speed << abs(val-25);
    foreach (auto path, path_dict) {
       path->speed = speed;
    }
}

void graphic_scene::timer_reset()
{
    auto timer = new QTimer(this);
    timer->setSingleShot(500);
    connect(timer, &QTimer::timeout, this, &graphic_scene::start_all_paths);

    foreach (auto road, path_dict) {
        road->timer->stop();
        road->m_vehicle->anim->stop();
        road->same = false;
        road->forward = true;
        road->start = 0.0;
        road->end = 1.0;
        road->active_line = 0;
        road->prev_line = -1;
        road->m_vehicle->position = 0.0;
    }
    timer->start();

}

void graphic_scene::reset_click_on_lines(int pos)
{
    for (int i = 0; i < vehicle_dict.count(); i++) {
        if (i != pos){
            if(vehicle_dict[i]->cliked == true){
                foreach (auto road, path_dict[i]->st_dict) {
                    road->setPen(QPen({def_road_color},3));
                }
                vehicle_dict[i]->cliked = false;
            }
        }
    }
}

void graphic_scene::check_clicked(int pos)
{
    reset_click_on_lines(pos);
    if(vehicle_dict[pos]->cliked == true)
    {
        foreach (auto road, path_dict[pos]->st_dict) {
            road->setPen(vehicle_dict[pos]->pen());
        }
        emit circle_clicked(path_dict[pos]);
        /*
        for (int i = 0; i < path_dict[pos]->st_dict.count(); i++) {
            auto road = path_dict[pos]->st_dict[i];
            road->setPen(vehicle_dict[pos]->pen());
            if( i < path_dict[pos]->active_line && road->station != -1){
                qDebug() << "passed: " << i;
            }else if(i > path_dict[pos]->active_line && road->station != -1){
                qDebug() << "future: " << i;
            }else if(i == path_dict[pos]->active_line && road->station != -1){
                if(path_dict[pos]->m_vehicle->position > road->station){
                    qDebug() << "passed: " << i;
                }else{
                    qDebug() << "future: " << i;
                }
            }
        }
        */
    }
    else if (vehicle_dict[pos]->cliked == false)
    {
        foreach (auto road, path_dict[pos]->st_dict) {
            road->setPen(QPen({def_road_color},3));
        }
        emit circle_unclicked();
    }
    //qDebug() << pos;
}

void graphic_scene::start_all_paths()
{
    foreach (auto road, path_dict) {
        road->timer->start();
    }
}
