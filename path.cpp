#include "path.h"
#include <QTimer>
#include  <QDebug>

path::path(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &path::move);
    //timer->start();
}

void path::find_corr_way()
{
    bool corrected = false;
    int first = 1;
    for (int i = 1 ; i < st_dict.count();i++) {
        if(st_dict[i-1]->line().p2() != st_dict[i]->line().p1() && corrected == false){
            //qDebug() << "correcting way" << i;
            wrong_direction_dict.push_back(i);
            corrected = true;
            first = 2;
        }else if(corrected == true){
            if(st_dict[i-1]->line().p1() != st_dict[i]->line().p1()){
                //qDebug() << "correcting way (before corrected)" << i;
                wrong_direction_dict.push_back(i);
            }
            corrected = false;
        }
        else if(first == 1){
            first = 0;
        }

    }
    //qDebug() << wrong_direction_dict;
    if(first == 2){
        if(std::find(wrong_direction_dict.begin(),wrong_direction_dict.end(), 1) != wrong_direction_dict.end() && std::find(wrong_direction_dict.begin(),wrong_direction_dict.end(), 2) != wrong_direction_dict.end()){
            wrong_direction_dict.clear();
            wrong_direction_dict.push_back(0);
            corrected = true;
            for (int i = 1 ; i < st_dict.count();i++) {
                if(st_dict[i-1]->line().p2() != st_dict[i]->line().p1() && corrected == false){
                    //qDebug() << "correcting way" << i;
                    wrong_direction_dict.push_back(i);
                    corrected = true;
                }else if(corrected == true){
                    if(st_dict[i-1]->line().p1() != st_dict[i]->line().p1()){
                        //qDebug() << "correcting way (before corrected)" << i;
                        wrong_direction_dict.push_back(i);
                    }
                    corrected = false;
                }
            }

        }
    }
    //qDebug() << wrong_direction_dict;
}

void path::start_this()
{
    timer->start();
}

void path::move()
{
    if(end_me == true){
        qDebug() << "ended";
        //int my_pos = m_vehicle->pos_in_dict;
        delete m_vehicle;
        timer->stop();
        //emit delete_me(my_pos);
        return;
    }

    auto line = st_dict[active_line];
    //auto veh_pos = m_vehicle->pos_in_dict;

    //line->time_line(m_vehicle->pos_in_dict);

    auto tmp_start = start;
    auto tmp_end = end;

    if(std::find(wrong_direction_dict.begin(),wrong_direction_dict.end(), active_line) != wrong_direction_dict.end()){
        //qDebug() << "correcting way";
        tmp_start = end;
        tmp_end = start;
    }

    if(prev_line != -1){
        st_dict[prev_line]->remove_vehicle(m_vehicle->pos_in_dict);
        //qDebug() <<st_dict[prev_line]->line().p1() - st_dict[prev_line]->line().p2() << line->line().p1() - line->line().p2() <<(st_dict[prev_line]->line().p1() - st_dict[prev_line]->line().p2()) - (line->line().p1() - line->line().p2());
    }

    prev_line = active_line;

    //line->vehicle_dict[m_vehicle->pos_in_dict] = m_vehicle;
    line->add_vehicle(m_vehicle,m_vehicle->pos_in_dict);


    m_vehicle->anim->setEndValue(tmp_end);
    m_vehicle->anim->setStartValue(tmp_start);
    timer->setInterval((line->duration + line->delay + 20) * speed);
    m_vehicle->anim->setDuration((line->duration + line->delay) * speed);

    if((line->station != -1) && (same == false) && (std::find(stations.begin(),stations.end(), line->pos) != stations.end())){
        m_vehicle->anim->setEndValue(line->station);
        timer->setInterval((((line->duration + line->delay) * (std::abs(tmp_start - line->station))) + pause) * speed);
        m_vehicle->anim->setDuration(((line->duration + line->delay) * (std::abs(tmp_start - line->station))) * speed);
        if(line->pos == stations.back() && (forward == true))
        {
            forward = false;
            start = 1.0;
            end = 0.0;
            active_line++;
            timer->setInterval(timer->remainingTime() + pause*speed);
        }
        else if(line->pos == stations.front() && (forward == false))
        {
            forward = true;
            //start = 0.0;
            //end = 1.0;
            active_line--;
            //timer->setInterval(timer->remainingTime() - pause*speed);
            end_me = true;
        }else{
            forward == true ? active_line-- : active_line++;

        }
        same = true;

    }else if(same == true){
        m_vehicle->anim->setStartValue(line->station);
        timer->setInterval((((line->duration + line->delay) - ((line->duration + line->delay) * (std::abs(tmp_start - line->station)))) + 20) * speed);
        m_vehicle->anim->setDuration(((line->duration + line->delay) - ((line->duration + line->delay) * (std::abs(tmp_start - line->station)))) * speed);
        same = false;
    }

    m_vehicle->active = true;
    m_vehicle->anim->start();
    forward == true ? active_line++ : active_line--;
    anim_duration = m_vehicle->anim->duration();
    timer_duration = timer->interval();
    //qDebug() << "orig" << m_vehicle->anim->duration();
}

