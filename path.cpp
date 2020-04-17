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

void path::move()
{
    auto line = st_dict[active_line];

    line->anim->setEndValue(end);
    line->anim->setStartValue(start);
    timer->setInterval((line->duration+20)*speed);
    line->anim->setDuration(line->duration*speed);

    if((line->station != -1) && (same == false)){
        line->anim->setEndValue(line->station);
        timer->setInterval(((line->duration*(std::abs(start-line->station)))+pause)*speed);
        line->anim->setDuration((line->duration*(std::abs(start-line->station)))*speed);
        same = true;
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

    line->active = true;
    line->anim->start();

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
    }else if(active_line == -1){
        active_line++;
        forward = true;
        start = 0.0;
        end = 1.0;
        timer->setInterval(timer->remainingTime() + pause*speed);
    }
}
