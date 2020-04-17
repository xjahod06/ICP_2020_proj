#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QPen>
#include <QVariantAnimation>

class vehicle : public QObject
{
    Q_OBJECT
public:
    explicit vehicle(QObject *parent = nullptr);
    QPen m_pen{QPen({Qt::red},3)};
    int size{10};
    qreal position{0.0};
    bool active{false};
    QVariantAnimation *anim{nullptr};
    int pos_in_dict;


signals:

};

#endif // VEHICLE_H
