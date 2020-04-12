#include "custom_line.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>

custom_line::custom_line(QGraphicsItem *parent, QColor color):
    QObject(),
    QGraphicsLineItem(parent)
{
    setPen(QPen({color},3));
    //setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    anim = new QVariantAnimation(this);
    anim->setDuration(500);
    connect(anim, &QVariantAnimation::valueChanged, this, &custom_line::on_animation);

    if(color == Qt::blue){
        timer = new QTimer(this);
        timer->setInterval(2000);
        timer->start();

        connect(timer, &QTimer::timeout, this, &custom_line::time_line);
    }
}

void custom_line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos() << event->scenePos() << event->screenPos();

    anim->setStartValue(move);
    if(move == 0.0)
    {
        anim->setEndValue(1.0);
    }else{
        anim->setEndValue(0.0);
    }
    anim->setEasingCurve(QEasingCurve::InOutQuart);
    anim->start();

    QGraphicsLineItem::mousePressEvent(event);
}

void custom_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->drawLine(line());
    painter->drawEllipse(line().pointAt(move),10,10);
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
    anim->setStartValue(move);
    if(move == 0.0)
    {
        anim->setEndValue(1.0);
    }else{
        anim->setEndValue(0.0);
    }
    anim->setEasingCurve(QEasingCurve::InOutQuart);
    anim->start();
}

void custom_line::on_animation(const QVariant &value)
{
    move = value.toReal();
    update();
}
