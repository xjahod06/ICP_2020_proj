#ifndef PATH_H
#define PATH_H

#include <QObject>
#include "custom_line.h"
#include "vehicle.h"

class path : public QObject
{
    Q_OBJECT
public:
    explicit path(QObject *parent = nullptr);
    QMap<int, custom_line*> st_dict;
    vehicle *m_vehicle{nullptr};
    QTimer *timer;
    qreal speed{1.0};
    void find_corr_way();
    bool same{false};
    bool forward{true};
    qreal start{0.0};
    qreal end{1.0};
    int active_line{0};
    int prev_line{-1};
    std::list<int> wrong_direction_dict;
    int rem_duration{0};
    int anim_duration;
    int timer_duration;

private:
    int pause{1000};

private slots:
    void move();

signals:

};

#endif // PATH_H
