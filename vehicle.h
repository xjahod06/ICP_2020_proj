#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QPen>
#include <QVariantAnimation>
#include <QGraphicsEllipseItem>

class vehicle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit vehicle(QGraphicsItem *parent = nullptr);
    QPen m_pen{QPen({Qt::red},3)};
    int size{10};
    qreal position{0.0};
    bool active{false};
    QVariantAnimation *anim{nullptr};
    int pos_in_dict;
    void move_yourself_lazy_circle(QPointF paint_point);

private:
    QPointF center;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QRectF boundingRect() const override;

signals:

};

#endif // VEHICLE_H
