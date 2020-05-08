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
    for (int i = 1 ; i < st_dict.count();i++) {
        int decision;
        if(corrected == false){
            decision = is_connected(st_dict[i-1]->line(),st_dict[i]->line());
        }else{
            decision = is_connected(reverse_line(st_dict[i-1]->line()),st_dict[i]->line());
            corrected = false;
        }
        if(decision == 0){
            continue;
        }else if(decision == 1){
            wrong_direction_dict.push_back(i-1);
        }else if(decision == 2){
            wrong_direction_dict.push_back(i);
        }else if(decision == 3){
            wrong_direction_dict.push_back(i-1);
            wrong_direction_dict.push_back(i);
        }

    }
}

int path::is_connected(QLineF l1, QLineF l2)
{
    if(l1.p2() == l2.p1())
    {
        return 0; //all ok
    }else if(l1.p1() == l2.p1())
    {
        return 1; //correct 1
    }
    else if(l1.p2() == l2.p2())
    {
        return 2; //correct 2
    }
    else if(l1.p1() == l2.p2())
    {
        return 3; //correct both
    }
    else{
        return -1; //not connected
    }
}

QLineF path::reverse_line(QLineF line)
{
    return QLineF(line.p2(),line.p1());
}

void path::start_this()
{
    timer->start();
}

void path::reset_colors()
{
    foreach (auto road, st_dict) {
        road->setPen(QPen({road->m_pen.color()},3));
    }
}

void path::move()
{
    if(end_me == true){
        qDebug() << "ended";
        if(m_vehicle->cliked == true){
            reset_colors();
        }
        //int my_pos = m_vehicle->pos_in_dict;
        active = false;
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
        station_in_timer = true;
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
        station_in_timer = false;
    }

    m_vehicle->active = true;
    m_vehicle->anim->start();
    forward == true ? active_line++ : active_line--;
    anim_duration = m_vehicle->anim->duration();
    timer_duration = timer->interval();
    //qDebug() << "orig" << m_vehicle->anim->duration();
}

