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
    connect(anim, &QVariantAnimation::valueChanged, this, &custom_line::on_animation);

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
    //anim->setEasingCurve(QEasingCurve::InOutCirc);
    //anim->start();

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
    pp.addEllipse(line().pointAt(move), 10, 10);
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
    //qDebug() << anim->duration();
    /*
    if(m_pen.color() == Qt::blue){
        timer->setInterval(duration*2);
    }
    */

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
