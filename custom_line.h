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
    void time_line(int dict_pos);
    QPen m_pen{QPen({Qt::red},3)};
    bool active{false};
    int start_anim{0};
    int duration{1000};
    qreal station{-1};
    QVariantAnimation *anim{nullptr};
    QMap<int, vehicle*> vehicle_dict;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QRectF boundingRect() const override;

private:
    qreal move{0.0};
    QTimer *timer;
    void set_anim();
    bool anim_set{false};
    qreal move_1{0.0};
    bool active_1{false};
    QVariantAnimation *anim_1{nullptr};
    void test_anim(QVariantAnimation *animation, bool *active_anim, qreal *anim_move, vehicle *veh);


private slots:
    void on_animation(const QVariant &value);

};

#endif // CUSTOM_LINE_H
