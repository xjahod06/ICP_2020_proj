#include "custom_line.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>
#include <QMap>
#include "vehicle.h"

custom_line::custom_line(QColor m_color, QGraphicsItem *parent):
    QObject(),
    QGraphicsLineItem(parent)
{
    m_pen.setColor(m_color);
    setPen(m_pen);
    //setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
}

void custom_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsLineItem::mousePressEvent(event);
}

void custom_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->drawLine(line());
    painter->setPen(QPen({Qt::black},5));
    if(station != -1)
    {
        painter->drawEllipse(line().pointAt(station),2,2);
    }
    if(anim_set == false)
    {
        anim_set = true;
        set_anim();
        //qDebug() << line();
    }
}

QRectF custom_line::boundingRect() const
{
    QPainterPath pp;
    pp.addRect(QGraphicsLineItem::boundingRect());
    /*foreach (auto m_vehicle, vehicle_dict) {
        pp.addEllipse(line().pointAt(m_vehicle->position),m_vehicle->size+5,m_vehicle->size+5);
    }*/
    return pp.boundingRect();
}
/*
//qDebug() << vehicle_dict[dict_pos]->position;
//vehicle_dict[dict_pos]->anim = new QVariantAnimation(this);
//vehicle_dict[dict_pos]->anim->setDuration(duration);
//auto *actual_vehicle = vehicle_dict[dict_pos];
//connect(vehicle_dict[dict_pos]->anim, &QVariantAnimation::valueChanged, [this, dict_pos](){ test_anim(vehicle_dict[dict_pos]->anim,&(vehicle_dict[dict_pos]->active),&(vehicle_dict[dict_pos]->position)); });
*/
void custom_line::add_vehicle(vehicle *new_vehicle, int pos)
{
    vehicle_dict[pos] = new_vehicle;
    vehicle_dict[pos]->anim = new QVariantAnimation(this);
    connect(vehicle_dict[pos]->anim, &QVariantAnimation::valueChanged, [this, pos, new_vehicle](){test_anim(vehicle_dict[pos]->anim, &vehicle_dict[pos]->active, &vehicle_dict[pos]->position, new_vehicle);});

}

void custom_line::remove_vehicle(int pos)
{
    //disconnect(vehicle_dict[pos]->anim);
    this->disconnect();
    vehicle_dict.remove(pos);
}

void custom_line::set_anim()
{
    duration = line().length()*10.32;
    //set_direction();
}

void custom_line::test_anim(QVariantAnimation *animation, bool *active_anim, qreal *anim_move, vehicle* veh)
{
    *anim_move = animation->currentValue().toReal();
    if((*anim_move == 0.0) || (*anim_move == 1.0)){
        *active_anim = false;
    }else{
        *active_anim = true;
    }

    update();
    veh->move_yourself_lazy_circle(line().pointAt(veh->position));
}

void custom_line::set_direction()
{
    auto decision_point = line().p1() - line().p2();
    if(decision_point.x() == 0){
        if(decision_point.y() < 0)
        {
            direction = "down";
        }else{
            direction = "up";
        }
    }else if(decision_point.y() == 0){
        if(decision_point.x() > 0)
        {
            direction = "LR";
        }else{
            direction = "RL";
        }
    }else if(decision_point.x() < 0){
        direction = "RL";
    }else if(decision_point.x() > 0){
        direction = "LR";
    }
}
