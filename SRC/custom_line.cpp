/** ICP Project 2020 transport map
 * @file custom_line.cpp
 * @brief object ulice na mapě
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
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
    def_color = m_color;
    m_pen.setColor(m_color);
    setPen(m_pen);
    //setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
}

void custom_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(pen().color() != m_pen.color() && selected == false){
        return;
    }
    selected == true ? selected = false : selected = true;
    //selected == true ? setPen(QPen({QColor(255,120,120)},3)): setPen(m_pen);

    emit line_selected(this);

    qDebug() << "line clicked" << selected << pos;

    QGraphicsLineItem::mousePressEvent(event);
    update();
}

void custom_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(traffic_level > 0){
        painter->setPen(QPen({Qt::black},4));
        painter->drawLine(line());
    }
    if(selected == true){
        painter->setPen(QPen({Qt::cyan},10));
        painter->drawLine(line());
    }
    painter->setPen(pen());
    painter->drawLine(line());
    painter->setPen(QPen({Qt::black},5));
    if(station != -1)
    {
        if(selected_in_path == true){
            painter->setPen(QPen(pen().color(),6));
            painter->drawEllipse(line().pointAt(station),5,5);
            painter->setPen(QPen({Qt::black},5));
        }
        painter->drawEllipse(line().pointAt(station),2,2);
    }
    if(anim_set == false)
    {
        set_anim();
        //qDebug() << line();
    }
    if(station != -1 and station_time != ""){
        painter->drawText(line().pointAt(station).x()-5,line().pointAt(station).y()-5,station_time);
        painter->save();
        if(station_delay == "00:00"){
            painter->setPen(QPen(QColor(0,145,17),3));
        }else if(station_delay.at(0) != "+"){
            station_delay = "+"+station_delay;
            painter->setPen(QPen({Qt::red},3));
        }else{
            painter->setPen(QPen({Qt::red},3));
        }
        painter->drawText(line().pointAt(station).x()-5,line().pointAt(station).y()+15,station_delay);
        painter->restore();
    }
    painter->save();
    painter->translate(line().pointAt(0.5));
    //painter->rotate(-line().angle());
    if(0 < line().angle() && line().angle() < 90){
        painter->rotate(line().angle());
    }else if(91 < line().angle() && line().angle() < 180){
        painter->rotate(-line().angle()-180);
    }else if(181 < line().angle() && line().angle() < 270){
        painter->rotate(-line().angle()-180);
    }else if(271 < line().angle() && line().angle() < 360){
        painter->rotate(-line().angle());
    }

    painter->drawText(+5,-5,name);
    //painter->drawText(0,+10,QString::number(pos));
    painter->restore();
}

QRectF custom_line::boundingRect() const
{
    QPainterPath pp;
    pp.addRect(QGraphicsLineItem::boundingRect());
    return pp.boundingRect();
}

void custom_line::add_vehicle(vehicle *new_vehicle, int pos)
{
    vehicle_dict[pos] = new_vehicle;
    if(vehicle_dict[pos]->anim != nullptr){
        delete vehicle_dict[pos]->anim;
    }
    vehicle_dict[pos]->anim = new QVariantAnimation(this);
    connect(vehicle_dict[pos]->anim, &QVariantAnimation::valueChanged, [this, pos, new_vehicle](){test_anim(vehicle_dict[pos]->anim, &vehicle_dict[pos]->active, &vehicle_dict[pos]->position, new_vehicle);});

}

void custom_line::remove_vehicle(int pos)
{
    this->disconnect(vehicle_dict[pos]->anim);
    vehicle_dict.remove(pos);
}

void custom_line::set_anim()
{
    anim_set = true;
    duration = line().length()*40;
}

void custom_line::inc_traffic()
{
    if (traffic_level < 16){
        traffic_level++;
        delay = duration*(0.25*traffic_level);
        m_pen.setColor(QColor(255,255-traffic_level*16+1,255-traffic_level*16+1));
        setPen(m_pen);
        update();
        qDebug() << delay << pen().color();
    }
}

void custom_line::dec_traffic()
{
    if (traffic_level > 0){
        traffic_level--;
        if(traffic_level == 0){
            delay = 0;
            m_pen.setColor(def_color);
        }else{
            delay = duration*(0.25*traffic_level);
            m_pen.setColor(QColor(255,255-traffic_level*16,255-traffic_level*16));
        }
        setPen(m_pen);
        update();
        qDebug() << delay << pen().color();
    }
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
    if(veh != nullptr)
    {
        veh->move_yourself_lazy_circle(line().pointAt(veh->position));
    }
}
