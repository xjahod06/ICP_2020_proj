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
       if(path->m_vehicle->anim == NULL){
           continue;
       }
       if (path->m_vehicle->anim->state() == QAbstractAnimation::Running){
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
           path->timer->stop();
           if(path->station_in_timer == true){
               path->timer->setInterval( path->m_vehicle->anim->duration()+(path->pause*speed));
           }else{
               path->timer->setInterval( path->m_vehicle->anim->duration()+10);
           }
           path->timer->start();
       }else{
           path->timer->stop();
           path->timer->setInterval(path->timer->remainingTime()*speed);
           path->timer->start();
       }
    }
}

void graphic_scene::timer_reset()
{
    emit circle_unclicked();
    foreach (auto road, path_dict) {
        if(road->active == true){
            if(road->m_vehicle->anim != NULL){
                road->m_vehicle->anim->stop();
            }
            road->timer->stop();
            road->m_vehicle->disconnect();
            road->active = false;
            road->m_vehicle->hide = true;
            road->m_vehicle->update();
        }
        //delete(road->m_vehicle);
    }
    path_dict.clear();
    vehicle_dict.clear();
    emit reseted();
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

void graphic_scene::create_street(int street_id, QPointF start_p, QPointF end_p, QString street_name)
{
    st_dict[street_id] = new custom_line(def_road_color);
    st_dict[street_id]->setLine(QLineF(start_p,end_p));
    st_dict[street_id]->pos = street_id;
    st_dict[street_id]->name = street_name;
    addItem(st_dict[street_id]);
    connect(st_dict[street_id], &custom_line::line_selected, this, &graphic_scene::select_line);
}

void graphic_scene::create_station(int street_id, qreal position)
{
    st_dict[street_id]->station = position;
}

void graphic_scene::create_route(int route_id, QList<int> streets, QList<int> stations, QColor color)
{
    defined_path[route_id] = new path(this);
    foreach (auto road, streets) {
        defined_path[route_id]->st_dict[defined_path[route_id]->st_dict.count()] = st_dict[road];
    }
    foreach (auto station, stations) {
        defined_path[route_id]->stations.push_back(station);
    }
    defined_path[route_id]->find_corr_way();
    defined_path[route_id]->m_vehicle = new vehicle();
    defined_path[route_id]->m_vehicle->setPen(QPen({color},3));
    //generate_new_connection(route_id,0,0);
}

void graphic_scene::reset_scene()
{
    emit circle_unclicked();
    foreach (auto road, path_dict) {
        if(road->active == true){
            if(road->m_vehicle->anim != NULL){
                road->m_vehicle->anim->stop();
            }
            road->timer->stop();
            road->m_vehicle->disconnect();
            road->active = false;
        }
    }
    clear();
    path_dict.clear();
    vehicle_dict.clear();
    defined_path.clear();
    st_dict.clear();
    //emit road_clicked(nullptr);
    //emit circle_unclicked();
}

void graphic_scene::create_text(QString content, QPointF point, int font_size)
{
    QGraphicsTextItem *text = addText(content);
    text->setPos(point);
    QFont font_to_change = text->font();
    font_to_change.setPointSize(font_size);
    text->setFont(font_to_change);
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
                    road->selected_in_path = false;
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
            if(std::find(path_dict[pos]->stations.begin(),path_dict[pos]->stations.end(), road->pos) != path_dict[pos]->stations.end()){
                road->selected_in_path = true;
            }
        }
        emit circle_clicked(path_dict[pos]);
    }
    else if (vehicle_dict[pos]->cliked == false)
    {
        foreach (auto road, path_dict[pos]->st_dict) {
            road->setPen(road->m_pen);
            road->selected_in_path = false;
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
            int direction;
            if(line_subsequent(alternate_route[alternate_route.count()-1]->line(),selected_line->line(),&direction)){
                /*
                pos = is_in_map(path_dict[2]->st_dict,selected_line);
                remove_from_map(&path_dict[2]->st_dict,pos);
                int i = pos;
                foreach (auto insert_road, alternate_route) {
                    insert_into_map(&path_dict[2]->st_dict,i++,insert_road);
                }
                path_dict[1]->find_corr_way();
                */
                qDebug() << "path" << selected_line->pos << "closed";
                qDebug() << "objizdna trasa je:" << print_street_id(alternate_route);
                qDebug() << "actual:" << print_street_id(path_dict[0]->st_dict);
                qDebug() << defined_path.count();
                foreach (auto path, defined_path) {
                    auto pos = is_in_map(path->st_dict,selected_line);
                    if(pos != -1){
                        qDebug() << "before insert:" << print_street_id(path->st_dict);
                        remove_from_map(&(path->st_dict),pos);
                        foreach (auto road, alternate_route) {
                            insert_into_map(&(path->st_dict),pos++,road);
                        }
                        qDebug() << "after insert:" << print_street_id(path->st_dict);
                    }
                }
                foreach (auto path, path_dict) {
                    auto pos = is_in_map(path->st_dict,selected_line);
                    if(pos != -1){
                        qDebug() << "actual: " << path_dict.key(path) << pos;
                    }
                }

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

bool graphic_scene::line_subsequent(QLineF l1, QLineF l2,int *direction)
{
    if(l1.p1() == l2.p1() || l1.p2() == l2.p1())
    {
        *direction = 1;
        qDebug() << "navazuje" << *direction;
        return true;
    }else if(l1.p1() == l2.p2() || l1.p2() == l2.p2())
    {
        *direction = -1;
        qDebug() << "navazuje" << *direction;
        return true;
    }else
    {
        return false;
    }
}

QStringList graphic_scene::print_street_id(QMap<int, custom_line *> map)
{
    QStringList list;
    foreach (auto road, map) {
        list.push_back(QString::number(road->pos));
    }
    return list;
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
