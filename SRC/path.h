#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QLineF>
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
    bool same{true};
    bool forward{true};
    qreal start{0.0};
    qreal end{1.0};
    int active_line{0};
    int prev_line{-1};
    QList<int> wrong_direction_dict;
    std::list<int> stations;
    int rem_duration{0};
    int anim_duration;
    int timer_duration;
    int init_time{0};
    bool active{true};
    int start_min{0};
    int start_hour{0};
    bool end_me{false};
    bool station_in_timer{false};
    int pause{1000};

public slots:
    void start_this();

private:
    void reset_colors();
    int is_connected(QLineF l1,QLineF l2);
    QLineF reverse_line(QLineF line);

private slots:
    void move();

signals:
    void delete_me(int pos);

};

#endif // PATH_H
