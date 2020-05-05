#include "vehicle.h"
#include "custom_line.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>
#include "graphic_scene.h"

vehicle::vehicle(QGraphicsItem *parent) :
    QObject(),
    QGraphicsEllipseItem(parent)
{

}

void vehicle::move_yourself_lazy_circle(QPointF paint_point)
{
    //qDebug() << "inside:" << paint_point;
    center = paint_point;
    setRect(center.x()-size,center.y()-size,size*2,size*2);
    update();
    //qDebug() << "updated" << center << isVisible();
}

void vehicle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    cliked == true ? cliked = false : cliked = true;

    emit circle_clicked(pos_in_dict);

    //qDebug() << "clicked on circle" << cliked;

    //QGraphicsEllipseItem::mousePressEvent(event);
}

void vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   if(cliked == true){
       painter->setPen(QPen({Qt::cyan},10));
       painter->drawEllipse(rect());
   }
   painter->setPen(pen());
   painter->drawEllipse(rect());
   //painter->fillRect(rect(),QBrush(Qt::black));
   //painter->drawEllipse(center, size, size);
   //qDebug() << "__paint:" <<center;
}

QRectF vehicle::boundingRect() const
{
    QPainterPath pp;
    pp.addRect(QGraphicsEllipseItem::boundingRect());
    pp.addEllipse(center,size+5,size+5);
    return pp.boundingRect();
}
