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
    st_dict[0] = new custom_line(def_road_color);
    st_dict[0]->setLine(200,-50,0,0);
    st_dict[0]->station = 0.8;
    addItem(st_dict[0]);

    st_dict[1] = new custom_line(def_road_color);
    st_dict[1]->setLine(0,0,0,150);
    st_dict[1]->station = 0.8;
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

void graphic_scene::speed_change(int val)
{
    speed = abs(val-25)/15.0;
    qDebug() << "speed" <<speed;
}

void graphic_scene::timer_reset()
{
    auto timer = new QTimer(this);
    timer->setSingleShot(500);
    connect(timer, &QTimer::timeout, this, &graphic_scene::start_all_paths);

    foreach (auto road, path_dict) {
        road->timer->stop();
        road->m_vehicle->anim->stop();
        road->forward = false;
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
    static int active_line = 0;
    static bool forward = true;
    static qreal start = 0.0;
    static qreal end = 1.0;
    static int pause = 750;
    static bool same = false;

    auto line = st_dict[active_line];

    line->anim->setEndValue(end);
    line->anim->setStartValue(start);
    timer->setInterval((line->duration+20)*speed);
    line->anim->setDuration(line->duration*speed);

   // qDebug() << start << end << line->duration << same << timer->interval();

    if((line->station != -1) && (same == false)){
        line->anim->setEndValue(line->station);
        timer->setInterval(((line->duration*(std::abs(start-line->station)))+pause)*speed);
        line->anim->setDuration((line->duration*(std::abs(start-line->station)))*speed);
        same = true;
        //qDebug() << line->duration << std::abs(start-line->station) << line->duration*line->station;
        if(forward == true){
            active_line--;
        }else{
            active_line++;
        }

    }else if(same == true){
        line->anim->setStartValue(line->station);
        timer->setInterval(((line->duration - (line->duration*(std::abs(start-line->station))))+20)*speed);
        line->anim->setDuration((line->duration - (line->duration*(std::abs(start-line->station))))*speed);
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
        timer->setInterval(timer->remainingTime() + pause*speed);
        //qDebug() << timer->remainingTime(); //<< timer->remainingTimeAsDuration();
    }else if(active_line == -1){
        active_line++;
        forward = true;
        start = 0.0;
        end = 1.0;
        timer->setInterval(timer->remainingTime() + pause*speed);
    }

}

void graphic_scene::start_all_paths()
{
    foreach (auto road, path_dict) {
        road->timer->start();
    }
}
