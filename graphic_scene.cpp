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
    st_dict[0]->pos = 0;
    addItem(st_dict[0]);

    st_dict[1] = new custom_line(def_road_color);
    st_dict[1]->setLine(0,0,0,150);
    st_dict[1]->station = 0.8;
    st_dict[1]->pos = 1;
    addItem(st_dict[1]);

    st_dict[2] = new custom_line(def_road_color);
    st_dict[2]->setLine(0,150,200,150);
    st_dict[2]->pos = 2;
    addItem(st_dict[2]);

    st_dict[3] = new custom_line(def_road_color);
    st_dict[3]->setLine(300,300,200,150);
    st_dict[3]->station = 0.5;
    st_dict[3]->pos = 3;
    addItem(st_dict[3]);

    st_dict[4] = new custom_line(def_road_color);
    st_dict[4]->setLine(500,300,300,300);
    st_dict[4]->station = 0.75;
    st_dict[4]->pos = 4;
    addItem(st_dict[4]);

    st_dict[5] = new custom_line(def_road_color);
    st_dict[5]->setLine(500,0,500,300);
    st_dict[5]->station = 0.35;
    st_dict[5]->pos = 5;
    addItem(st_dict[5]);

    st_dict[6] = new custom_line(def_road_color);
    st_dict[6]->setLine(200,-50,200,150);
    st_dict[6]->station = 0.1;
    st_dict[6]->pos = 6;
    addItem(st_dict[6]);

    st_dict[7] = new custom_line(def_road_color);
    st_dict[7]->setLine(300,300,0,300);
    st_dict[7]->station = 0.45;
    st_dict[7]->pos = 7;
    addItem(st_dict[7]);

    st_dict[8] = new custom_line(def_road_color);
    st_dict[8]->setLine(200,-50,500,0);
    st_dict[8]->station = 0.2;
    st_dict[8]->pos = 8;
    addItem(st_dict[8]);

    foreach (auto st, st_dict) {
        connect(st, &custom_line::line_selected, this, &graphic_scene::select_line);
        qDebug() << st->pos << "connected";
    }

    vehicle_dict[0] = new vehicle();
    vehicle_dict[0]->setPen(QPen({Qt::blue},3));
    vehicle_dict[0]->pos_in_dict = 0;
    vehicle_dict[0]->setRect(0,0,0,0);
    addItem(vehicle_dict[0]);
    connect(vehicle_dict[0], &vehicle::circle_clicked, this, &graphic_scene::check_clicked);

    vehicle_dict[1] = new vehicle();
    vehicle_dict[1]->setPen(QPen({Qt::cyan},3));
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
        road->timer->setInterval(10);
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

void graphic_scene::toggle_timers()
{
    static bool active_timers = true;
    if(active_timers == true){
        foreach (auto path, path_dict) {
            path->timer->stop();
            path->m_vehicle->anim->pause();
            //qDebug() << path->m_vehicle->anim->state();
        }
        active_timers = false;
    }else{
        foreach (auto path, path_dict) {
            path->timer->start();
            if (path->m_vehicle->anim->state() == QAbstractAnimation::Paused){
                path->m_vehicle->anim->resume();
            }
        }
        active_timers = true;
    }
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
            if(road->selected == true){
                road->selected = false;
            }
        }
        emit circle_clicked(path_dict[pos]);
    }
    else if (vehicle_dict[pos]->cliked == false)
    {
        foreach (auto road, path_dict[pos]->st_dict) {
            road->setPen(road->m_pen);
        }
        emit circle_unclicked();
    }
    //qDebug() << pos;
}

void graphic_scene::select_line(custom_line *road)
{
    if(road->selected == true){
        reset_line_selection(road->pos);
        qDebug() << "clicked";
        emit road_clicked(road);

    }else{
        emit road_clicked(nullptr);
        qDebug() << "unclicked";
    }

}

void graphic_scene::reset_line_selection(int pos)
{
    for (int i = 0; i < st_dict.count();i++) {
        if(i != pos){
            if(st_dict[i]->selected == true){
                qDebug() << "reseted:" << i;
                //st_dict[i]->setPen(st_dict[i]->m_pen);
                st_dict[i]->selected = false;
                break;
            }
        }
    }
}

void graphic_scene::start_all_paths()
{
    foreach (auto road, path_dict) {
        road->timer->start();
    }
}
