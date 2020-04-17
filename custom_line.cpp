#include "custom_line.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>

custom_line::custom_line(QColor m_color, QGraphicsItem *parent):
    QObject(),
    QGraphicsLineItem(parent)
{
    m_pen.setColor(m_color);
    setPen(m_pen);
    //setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    anim = new QVariantAnimation(this);
    anim->setDuration(duration);
    //connect(anim, &QVariantAnimation::valueChanged, this, &custom_line::on_animation);
    connect(anim, &QVariantAnimation::valueChanged, [this](){ test_anim(anim,&active,&move); });
    anim_1 = new QVariantAnimation(this);
    connect(anim_1, &QVariantAnimation::valueChanged, [this](){ test_anim(anim_1,&active_1,&move_1); });

    /*
    if(m_pen.color() == Qt::blue){
        timer = new QTimer(this);
        timer->setInterval(duration*2);
        timer->start();

        connect(timer, &QTimer::timeout, this, &custom_line::time_line);
    }
    */
}

void custom_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << event->pos() << event->scenePos() << event->screenPos();

    //qDebug() << line().length()*5.16 << line().length()*5.16*2;
    /*
    anim->setStartValue(move);
    if(move == 0.0)
    {
        anim->setEndValue(1.0);
    }else{
        anim->setEndValue(0.0);
    }
    */

    //anim->setEasingCurve(QEasingCurve::InOutCirc)

    anim_1->setStartValue(0.0);
    anim_1->setEndValue(1.0);
    anim_1->setDuration(duration);
    anim_1->start();
    active_1 = true;


    QGraphicsLineItem::mousePressEvent(event);
}

void custom_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->drawLine(line());
    if(active == true)
    {
        painter->drawEllipse(line().pointAt(move),10,10);
    }

    if(active_1 == true)
    {
        painter->setPen(QPen({Qt::darkGray},3));
        painter->drawEllipse(line().pointAt(move_1),10,10);
    }

    /*
    foreach (auto m_vehicle, vehicle_dict) {
        painter->setPen(m_vehicle->m_pen_color);
        painter->drawEllipse(line().pointAt(m_vehicle->position),10,10);
    }
    */
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
    pp.addEllipse(line().pointAt(move), 15, 15);
        pp.addEllipse(line().pointAt(move_1),15,15);
    return pp.boundingRect();
}

void custom_line::time_line()
{
    //anim->setStartValue((qreal)abs(start_anim));
    /*
    anim->setStartValue(move);

    if(move == 0.0)
    {
        anim->setEndValue(1.0);
    }else{
        anim->setEndValue(0.0);
    }
    */
    //anim->setEndValue((qreal)abs(start_anim-1));
    //anim->setEasingCurve(QEasingCurve::InOutQuart);
    //qDebug() << anim->endValue() << anim->startValue();
    active = true;
    anim->start();
}

void custom_line::set_anim()
{
    duration = line().length()*5.16;
    //qDebug() << line().length() << duration;
    anim->setDuration(duration);
    anim_1->setDuration(duration);
    //qDebug() << anim->duration();
    /*
    if(m_pen.color() == Qt::blue){
        timer->setInterval(duration*2);
    }
    */

}

void custom_line::test_anim(QVariantAnimation *animation, bool *active_anim, qreal *anim_move)
{
    //qDebug() << animation->currentValue() << animation->currentTime() << animation->duration() << animation->currentValue().toReal();
    *anim_move = animation->currentValue().toReal();
    if((*anim_move == 0.0) || (*anim_move == 1.0)){
        //qDebug() << "end of anim";
        *active_anim = false;
    }else{
        *active_anim = true;
    }

    update();
}

void custom_line::on_animation(const QVariant &value)
{
    move = value.toReal();
    update();

    if((move == 0.0) || (move == 1.0)){
        //qDebug() << "end of anim";
        active = false;
    }else{
        active = true;
    }

}
