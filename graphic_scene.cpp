#include "graphic_scene.h"
#include "custom_line.h"
#include "path.h"
#include <QGraphicsItem>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QThread>

graphic_scene::graphic_scene(QObject *parent) :
    QGraphicsScene(parent)
{
    /*e
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
    }

    defined_path[0] = new path(this);
    defined_path[0]->st_dict[0] = st_dict[0];
    defined_path[0]->st_dict[1] = st_dict[1];
    defined_path[0]->st_dict[2] = st_dict[2];
    defined_path[0]->st_dict[3] = st_dict[3];
    defined_path[0]->st_dict[4] = st_dict[7];
    defined_path[0]->stations.push_back(0);
    defined_path[0]->stations.push_back(1);
    defined_path[0]->stations.push_back(7);
    defined_path[0]->find_corr_way();
    defined_path[0]->m_vehicle = new vehicle();
    defined_path[0]->m_vehicle->setPen(QPen({Qt::blue},3));

    defined_path[1] = new path(this);
    defined_path[1]->st_dict[0] = st_dict[3];
    defined_path[1]->st_dict[1] = st_dict[4];
    defined_path[1]->st_dict[2] = st_dict[5];
    defined_path[1]->st_dict[3] = st_dict[8];
    defined_path[1]->stations.push_back(3);
    defined_path[1]->stations.push_back(4);
    defined_path[1]->stations.push_back(5);
    defined_path[1]->stations.push_back(8);
    defined_path[1]->find_corr_way();
    defined_path[1]->m_vehicle = new vehicle();
    defined_path[1]->m_vehicle->setPen(QPen({Qt::cyan},3));

    defined_path[2] = new path(this);
    defined_path[2]->st_dict[0] = st_dict[6];
    defined_path[2]->st_dict[1] = st_dict[3];
    defined_path[2]->st_dict[2] = st_dict[7];
    defined_path[2]->stations.push_back(6);
    defined_path[2]->stations.push_back(3);
    defined_path[2]->stations.push_back(7);
    defined_path[2]->find_corr_way();
    defined_path[2]->m_vehicle = new vehicle();
    defined_path[2]->m_vehicle->setPen(QPen({Qt::green},3));
    */
    //generate_new_connection(0,0,0);
    //generate_new_connection(1,0,0);
    //generate_new_connection(2,0,0);

    //path_dict[0]->timer->start();
    //path_dict[1]->timer->start();
    //path_dict[2]->timer->start();
    /*
    QMap<int, custom_line*> test;
    test[0] = st_dict[0];
    test[1] = st_dict[1];
    test[2] = st_dict[2];
    test[3] = st_dict[3];

    foreach (auto to_print, test) {
        fprintf(stderr,"%i, ",to_print->pos);
        fflush(stderr);
    }
    qDebug() << "";

    insert_into_map(&test,1,st_dict[4]);
    foreach (auto to_print, test) {
        fprintf(stderr,"%i, ",to_print->pos);
        fflush(stderr);
    }
    qDebug() << "";
    */



}

void graphic_scene::speed_change(int val)
{
    speed = abs(val-25)/15.0;
    qDebug() << "speed" << speed << abs(val-25);
    foreach (auto path, path_dict) {
       if(path->active == false){
           continue;
       }
       path->speed = speed;
       if (path->m_vehicle->anim->state() == QAbstractAnimation::Running){
           //qDebug() << path->m_vehicle->anim->startValue().toDouble() << path->m_vehicle->anim->endValue().toDouble() << path->m_vehicle->anim->duration() << path->m_vehicle->position;
           //qDebug() << path->m_vehicle->anim->duration() / std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->anim->endValue().toDouble()) * std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->position);
           //qDebug() << path->m_vehicle->anim->duration() - (path->m_vehicle->anim->duration() / std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->anim->endValue().toDouble()) * std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->position));
           int rem_anim_time = path->anim_duration - (path->anim_duration / std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->anim->endValue().toDouble()) * std::abs(path->m_vehicle->anim->startValue().toDouble() - path->m_vehicle->position));
           path->m_vehicle->anim->stop();
           path->m_vehicle->anim->setStartValue(path->m_vehicle->position);
           path->m_vehicle->anim->setDuration(rem_anim_time*path->speed);
           path->m_vehicle->anim->start();
           //qDebug() << path->m_vehicle->anim->startValue().toDouble() << path->m_vehicle->anim->endValue().toDouble() << path->m_vehicle->anim->duration();
           if(speed == 1.0){
             qDebug() << path->m_vehicle->anim->duration() << path->anim_duration;
           }
           //qDebug() << "_____________________________________________________________________________";
       }
       int rem_time = path->timer->remainingTime();
       path->timer->stop();
       path->timer->setInterval(rem_time*speed);
       path->timer->start();
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
        road->same = true;
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
            if(path->active == false){
                continue;
            }
            path->rem_duration = path->timer->remainingTime();
            qDebug() << path->rem_duration;
            path->timer->stop();
            path->m_vehicle->anim->pause();
            //qDebug() << path->m_vehicle->anim->state();
        }
        active_timers = false;
    }else{
        foreach (auto path, path_dict) {
            if(path->active == false){
                continue;
            }
            path->timer->setInterval(path->rem_duration);
            path->timer->start();
            if (path->m_vehicle->anim->state() == QAbstractAnimation::Paused){
                path->m_vehicle->anim->resume();
            }
        }
        active_timers = true;
    }
}

void graphic_scene::create_street(int street_id, QPointF start_p, QPointF end_p)
{
    qDebug() << "huh";
    st_dict[street_id] = new custom_line(def_road_color);
    st_dict[street_id]->setLine(QLineF(start_p,end_p));
    st_dict[street_id]->pos = street_id;
    addItem(st_dict[street_id]);
    qDebug() << start_p << end_p << st_dict[street_id]->line() << QLineF(start_p,end_p);
}

void graphic_scene::generate_new_connection(int pos, int min, int hour)
{
    path *path_pattern = defined_path[pos];
    int inserted_pos = path_dict.count();
    path_dict[inserted_pos] = new path(this);
    path_dict[inserted_pos]->st_dict = path_pattern->st_dict;
    path_dict[inserted_pos]->stations = path_pattern->stations;
    path_dict[inserted_pos]->wrong_direction_dict = path_pattern->wrong_direction_dict;
    vehicle_dict[inserted_pos] = new vehicle();
    path_dict[inserted_pos]->m_vehicle = vehicle_dict[inserted_pos];
    path_dict[inserted_pos]->m_vehicle->setPen(path_pattern->m_vehicle->pen());
    path_dict[inserted_pos]->m_vehicle->setRect(0,0,0,0);
    path_dict[inserted_pos]->m_vehicle->pos_in_dict = inserted_pos;
    addItem(path_dict[inserted_pos]->m_vehicle);
    connect(path_dict[inserted_pos]->m_vehicle, &vehicle::circle_clicked, this, &graphic_scene::check_clicked);
    path_dict[inserted_pos]->timer->start();
    connect(path_dict[inserted_pos], &path::delete_me, this, &graphic_scene::delete_path);
    path_dict[inserted_pos]->start_min = min;
    path_dict[inserted_pos]->start_hour = hour;
    path_dict[inserted_pos]->speed = speed;
    //qDebug() << hour << min;
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
    static int pos_in_alternate_route = 0;
    if(line_selecting_for_close == false){
        if(road->selected == true){
            reset_line_selection(road->pos);
            qDebug() << "clicked";
            emit road_clicked(road);
            selected_line = road;

        }else{
            emit road_clicked(nullptr);
            qDebug() << "unclicked";
        }
    }else{
        int pos = is_in_map(alternate_route,road);
        if(pos != -1){
            qDebug() << road->pos << "removed";
            remove_from_map(&alternate_route,pos);
            pos_in_alternate_route--;
        }else{
            qDebug() << road->pos << "added";
            alternate_route[pos_in_alternate_route] = road;
            pos_in_alternate_route++;
        }
        if(alternate_route.count() > 1){
            /*
            foreach (auto st, alternate_route) {
                qDebug() << st->pos;
            }
            */
            if(line_subsequent(alternate_route[alternate_route.count()-1]->line(),selected_line->line())){
                qDebug() << "wuiiiii";
                pos = is_in_map(path_dict[2]->st_dict,selected_line);
                qDebug() << pos;
                foreach (auto to_print, alternate_route) {
                    fprintf(stderr,"%i, ",to_print->pos);
                    fflush(stderr);
                }
                qDebug() << "";
                foreach (auto to_print, path_dict[2]->st_dict) {
                    fprintf(stderr,"%i, ",to_print->pos);
                    fflush(stderr);
                }
                qDebug() << "";
                remove_from_map(&path_dict[2]->st_dict,pos);
                foreach (auto to_print, path_dict[2]->st_dict) {
                    fprintf(stderr,"%i, ",to_print->pos);
                    fflush(stderr);
                }
                qDebug() << "";
                int i = pos;
                foreach (auto insert_road, alternate_route) {
                    insert_into_map(&path_dict[2]->st_dict,i++,insert_road);
                }
                foreach (auto to_print, path_dict[2]->st_dict) {
                    fprintf(stderr,"%i, ",to_print->pos);
                    fflush(stderr);
                }
                qDebug() << "";
                path_dict[1]->find_corr_way();

            }
        }
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

QMap<int, custom_line *> graphic_scene::insert_into_map(QMap<int, custom_line *> *map, int index, custom_line *value)
{
    custom_line *stores_value;
    custom_line *insert_vale = value;
    for (int i = index; i < map->count();i++) {
        stores_value = (*map)[i];
        (*map)[i] = insert_vale;
        insert_vale = stores_value;
    }
    (*map)[map->count()] = insert_vale;

    return *map;
}

QMap<int, custom_line *> graphic_scene::remove_from_map(QMap<int, custom_line *> *map, int index)
{
    //map.remove(index);
    for (int i = index; i < map->count()-1; i++) {
        (*map)[i] = (*map)[i+1];
    }
    map->remove(map->count()-1);
    return *map;
}

int graphic_scene::is_in_map(QMap<int, custom_line *> map, custom_line *value)
{
    for (int i = 0; i < map.count();i++) {
        //qDebug() << value->pos << map[i]->pos;
        if(value->pos == map[i]->pos){
            return i;
        }
    }
    return -1;
}

bool graphic_scene::line_subsequent(QLineF l1, QLineF l2)
{
    if(l1.p1() == l2.p1() || l1.p1() == l2.p2())
    {
        qDebug() << "navazuje";
        return true;
    }else if(l1.p2() == l2.p1() || l1.p2() == l2.p2())
    {
        qDebug() << "navazuje";
        return true;
    }else
    {
        return false;
    }
}

void graphic_scene::start_all_paths()
{
    foreach (auto path, path_dict) {
        if(path->active == false){
            continue;
        }
        path->timer->start();
    }
}

void graphic_scene::delete_path(int pos)
{
    vehicle_dict.remove(pos);
    path_dict.remove(pos);
    for(int i = pos; i < path_dict.count()+1;i++){
        path_dict[i] = path_dict[i+1];
        vehicle_dict[i] = vehicle_dict[i+1];
    }
}
