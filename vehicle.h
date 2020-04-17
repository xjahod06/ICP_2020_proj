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
    int size{15};
    qreal position{0.0};
    QVariantAnimation *anim{nullptr};

signals:

};

#endif // VEHICLE_H
