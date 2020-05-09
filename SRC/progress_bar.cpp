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
    /*
    auto time = convert_time(m_hour,m_minute);
    if(m_connected == true){
        foreach (auto road, st_dict) {
             road->station_time = time;
        }
        update();
    }
    */

}

void progress_bar::show_path(path *active_path)
{
    if(active_path->end_me == true){
        return;
    }
    clear();
    def_hour = 0;
    def_minute = 0;
    total_path_duration = 0;
    new_line = false;
    st_dict.clear();
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

    stations = active_path->stations;

    //qDebug() << stations << "orig: " <<active_path->stations;

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
        st_dict[i]->set_anim();
        st_dict[i]->duration = road->duration;
        st_dict[i]->delay = road->delay;
        st_dict[i]->pos = road->pos;
        start = end;
        if((std::find(stations.begin(),stations.end(), st_dict[i]->pos) == stations.end())){
            st_dict[i]->station = -1;
        }
        i++;
    }

    m_vehicle = new vehicle();
    m_vehicle->setPen(active_path->m_vehicle->pen());
    m_vehicle->pos_in_dict = 1;
    m_vehicle->setRect(0,0,0,0);
    addItem(m_vehicle);

    m_vehicle->position = active_path->m_vehicle->position;
    same = active_path->same;
    forward = active_path->forward;
    if(forward == true){
        start = 0.0;
        end = 1.0;
    }else{
        start = 1.0;
        end = 0.0;
    }
    active_line = active_path->active_line;
    //prev_line = active_path->prev_line;
    prev_line = -1;

    speed = &active_path->speed;

    m_timer = &active_path->timer;

    connect(*m_timer, &QTimer::timeout, this, &progress_bar::launch);
    m_connected = true;
    //launch();
    def_minute = active_path->start_min;
    def_hour = active_path->start_hour;
    delay_to_station(forward);

    //qDebug() << active_path->st_dict.keys() << st_dict.keys();

}

void progress_bar::reset_path()
{
    if(m_connected == false){
        return;
    }
    clear();
    m_connected = false;
    //disconnect(*m_timer, &QTimer::timeout, this, &progress_bar::launch);
    disconnect(*m_timer,&QTimer::timeout,this,&progress_bar::launch);
    qDebug() << "reseted";
    def_hour = 0;
    def_minute = 0;
    total_path_duration = 0;
    new_line = false;
    update();
    st_dict.clear();
}

QString progress_bar::convert_to_time(qreal both)
{
    int min = (int)both % 60;
    int hour = div(both,60).quot;
    return convert_time(hour,min);
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

int progress_bar::time_to_ms(int hour, int min)
{
    int total_time = 0;
    total_time += (min * 1000);
    total_time += (hour * 60 * 1000);
    return total_time;
}

void progress_bar::delay_to_station(bool forward)
{
    int total_duration = time_to_ms(def_hour,def_minute);
    int total_delay = 0;
    ///qDebug() << total_duration;
    if(forward == true)
    {
        st_dict[0]->station_time = convert_to_time(total_duration/1000);
        total_duration += pause;
        total_duration += (1 - st_dict[0]->station)*st_dict[0]->duration;
        total_delay += (1 - st_dict[0]->station)*st_dict[0]->delay;

        for (int i = 1 ;i < st_dict.count()-1;i++) {
            if((st_dict[i]->station != -1) && (std::find(stations.begin(),stations.end(), st_dict[i]->pos) != stations.end())){
                total_duration += pause;
                st_dict[i]->station_time = convert_to_time((total_duration + (st_dict[i]->station * st_dict[i]->duration)) / 1000);
                st_dict[i]->station_delay = convert_to_time((total_delay + (st_dict[i]->station * st_dict[i]->delay)) / 1000);
            }
            total_duration += st_dict[i]->duration + 20;
            total_delay += st_dict[i]->delay;
        }
        total_duration += st_dict[st_dict.count()-1]->station * st_dict[st_dict.count()-1]->duration;
        total_delay += st_dict[st_dict.count()-1]->station * st_dict[st_dict.count()-1]->delay;
        st_dict[st_dict.count()-1]->station_time = convert_to_time(total_duration/1000);
        st_dict[st_dict.count()-1]->station_delay = convert_to_time(total_delay/1000);
    }
    else
    {
        foreach (auto road, st_dict) {
            total_duration += road->duration +20;
            total_delay += road->delay;
            if((road->station != -1) && (std::find(stations.begin(),stations.end(), road->pos) != stations.end())){
                total_duration += pause;
            }
        }
        total_duration -= (1 - st_dict[st_dict.count()-1]->station) * st_dict[st_dict.count()-1]->duration;
        total_delay -= (1 - st_dict[st_dict.count()-1]->station) * st_dict[st_dict.count()-1]->delay;

        total_duration -= (st_dict[0]->station) * st_dict[0]->duration;
        total_delay -= (st_dict[0]->station) * st_dict[0]->delay;

        st_dict[st_dict.count()-1]->station_time = convert_to_time(total_duration/1000);
        total_duration += pause;
        total_duration += st_dict[st_dict.count()-1]->station * st_dict[st_dict.count()-1]->duration;
        total_delay += st_dict[st_dict.count()-1]->station *  st_dict[st_dict.count()-1]->delay;

        for (int i = st_dict.count()-2 ;i > 0;i--) {
            if((st_dict[i]->station != -1) && (std::find(stations.begin(),stations.end(), st_dict[i]->pos) != stations.end())){
                total_duration += pause;
                st_dict[i]->station_time = convert_to_time((total_duration + ((1-st_dict[i]->station) * st_dict[i]->duration)) / 1000);
                st_dict[i]->station_delay = convert_to_time((total_delay + ((1-st_dict[i]->station) * st_dict[i]->delay)) / 1000);
            }
            total_duration += st_dict[i]->duration + 20;
            total_delay += st_dict[i]->delay;
        }
        total_duration += (1-st_dict[0]->station) * st_dict[st_dict.count()-1]->duration;
        total_delay += (1-st_dict[0]->station) * st_dict[st_dict.count()-1]->delay;
        st_dict[st_dict.count()-1]->station_time = convert_to_time(total_duration/1000);
        st_dict[st_dict.count()-1]->station_delay = convert_to_time(total_delay/1000);
    }

}

void progress_bar::launch()
{
    //delay_to_station();
    //qDebug() << "tick";

    if(end_of_road == true){
        end_of_road = false;
        reset_path();
        return;
    }

    if(new_line == true){
        //def_hour = m_hour;
        //def_minute = m_minute;
        delay_to_station(forward);
        new_line = false;
    }

    auto line = st_dict[active_line];

    if(prev_line > -1){
        st_dict[prev_line]->remove_vehicle(m_vehicle->pos_in_dict);
    }

    prev_line = active_line;

    line->add_vehicle(m_vehicle,m_vehicle->pos_in_dict);

    m_vehicle->anim->setEndValue(end);
    m_vehicle->anim->setStartValue(start);
    m_vehicle->anim->setDuration((line->duration + line->delay) * *speed);

     if((line->station != -1) && (same == false) && (std::find(stations.begin(),stations.end(), line->pos) != stations.end())){
        m_vehicle->anim->setEndValue(line->station);
        m_vehicle->anim->setDuration(((line->duration + line->delay) * (std::abs(start - line->station))) * *speed);
        if(line->pos == stations.back() && (forward == true))
        {
            forward = false;
            start = 1.0;
            end = 0.0;
            active_line++;
            new_line = true;
        }
        else if(line->pos == stations.front() && (forward == false))
        {
            end_of_road = true;
        }
        else{
            forward == true ? active_line-- : active_line++;

        }
        same = true;

    }else if(same == true){
        m_vehicle->anim->setStartValue(line->station);
        m_vehicle->anim->setDuration(((line->duration + line->delay) - (line->duration * (std::abs(start - line->station)))) * *speed);
        same = false;
    }

    m_vehicle->active = true;
    m_vehicle->anim->start();
    forward == true ? active_line++ : active_line--;
    //qDebug() << "progress: " << m_vehicle->anim->duration();
}
