#include "progress_bar.h"
#include <QDebug>
#include "custom_line.h"
#include "path.h"

progress_bar::progress_bar(QObject *parent) :
    QGraphicsScene(parent)
{
}

void progress_bar::sync_self_clock(int hour, int min)
{
    m_hour = hour;
    m_minute = min;
    auto time = convert_time(m_hour,m_minute);
    if(m_connected == true){
        foreach (auto road, st_dict) {
             road->station_time = time;
        }
        update();
    }

}

void progress_bar::show_path(path *active_path)
{
    clear();
    if(m_connected == true){
        disconnect(*m_timer,&QTimer::timeout,this,&progress_bar::launch);
    }
    int i = 0;
    qreal start = 0.0;
    qreal total_length = 0;
    foreach (auto road, active_path->st_dict) {
        total_length += road->line().length();
    }
    //qDebug() << total_length << m_width << (m_width-30)/total_length;
    qreal correcter = (m_width-30-(active_path->m_vehicle->size*2 + active_path->m_vehicle->size))/total_length;
    foreach (auto road, active_path->st_dict) {
        qreal end = start+(road->line().length()*correcter);
        //qDebug() << "start: " << start << "end" << end;
        st_dict[i] = new custom_line(active_path->m_vehicle->pen().color());
        st_dict[i]->setLine(start,0,start+road->line().length()*correcter,0);
        if(std::find(active_path->wrong_direction_dict.begin(),active_path->wrong_direction_dict.end(), i) != active_path->wrong_direction_dict.end()){
            st_dict[i]->station = 1 - road->station;
        }
        else{
            st_dict[i]->station = road->station;
        }
        addItem(st_dict[i]);
        st_dict[i]->station_time = convert_time(m_hour,m_minute);
        start = end;
        i++;
    }
    if(m_vehicle == nullptr){
    }
    m_vehicle = new vehicle();
    m_vehicle->setPen(active_path->m_vehicle->pen());
    m_vehicle->pos_in_dict = 1;
    m_vehicle->setRect(0,0,0,0);
    addItem(m_vehicle);

    m_vehicle->position = active_path->m_vehicle->position;
    same = active_path->same;
    forward = active_path->forward;
    start = active_path->start;
    end = active_path->end;
    active_line = active_path->active_line;
    prev_line = active_path->prev_line;

    speed = &active_path->speed;

    m_timer = &active_path->timer;

    connect(*m_timer, &QTimer::timeout, this, &progress_bar::launch);
    m_connected = true;
    //launch();

}

void progress_bar::reset_path()
{
    clear();
    m_connected = false;
    //disconnect(*m_timer, &QTimer::timeout, this, &progress_bar::launch);
    disconnect(*m_timer,&QTimer::timeout,this,&progress_bar::launch);
    qDebug() << "reseted";
    update();
}

QString progress_bar::convert_time(int hour, int min)
{
    QString min_string;
    QString hour_string;

    min_string.setNum(min);
    hour_string.setNum(hour);

    QString final_text;

    if(hour < 10){
        final_text += "0";
    }
    final_text += hour_string + ":";

    if(min < 10){
        final_text += "0";
    }
    final_text += min_string;

    return final_text;
}

void progress_bar::launch()
{
    //qDebug() << "tick";
    auto line = st_dict[active_line];

    if(prev_line > -1){
        st_dict[prev_line]->remove_vehicle(m_vehicle->pos_in_dict);
    }

    prev_line = active_line;

    line->add_vehicle(m_vehicle,m_vehicle->pos_in_dict);

    m_vehicle->anim->setEndValue(end);
    m_vehicle->anim->setStartValue(start);
    m_vehicle->anim->setDuration(line->duration * *speed);

    if((line->station != -1) && (same == false)){
        m_vehicle->anim->setEndValue(line->station);
        m_vehicle->anim->setDuration((line->duration * (std::abs(start - line->station))) * *speed);
        same = true;
        if(forward == true){
            active_line--;
        }else{
            active_line++;
        }

    }else if(same == true){
        m_vehicle->anim->setStartValue(line->station);
        m_vehicle->anim->setDuration((line->duration - (line->duration * (std::abs(start - line->station)))) * *speed);
        same = false;
    }

    m_vehicle->active = true;
    m_vehicle->anim->start();

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
    }else if(active_line == -1){
        active_line++;
        forward = true;
        start = 0.0;
        end = 1.0;
    }
    //qDebug() << "progress: " << m_vehicle->anim->duration();
}
