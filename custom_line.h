#ifndef CUSTOM_LINE_H
#define CUSTOM_LINE_H

#include <QGraphicsLineItem>
#include <QVariantAnimation>
#include <QTimer>
#include <QPen>
#include "vehicle.h"

class custom_line :public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit custom_line(QColor m_color = Qt::red, QGraphicsItem *parent = nullptr);
    QPen m_pen{QPen({Qt::red},3)};
    int duration{1000};
    qreal station{-1};
    QMap<int, vehicle*> vehicle_dict;
    void add_vehicle(vehicle* new_vehicle,int pos);
    void remove_vehicle(int pos);
    QString direction;
    QVariantAnimation *anim{nullptr};
    qreal move{0.0};

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QRectF boundingRect() const override;

private:
    QTimer *timer;
    void set_anim();
    bool anim_set{false};
    void test_anim(QVariantAnimation *animation, bool *active_anim, qreal *anim_move, vehicle* veh = nullptr);
    void set_direction();

};

#endif // CUSTOM_LINE_H
