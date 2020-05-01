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
    bool same{true};
    bool forward{true};
    qreal start{0.0};
    qreal end{1.0};
    int active_line{0};
    int prev_line{-1};
    std::list<int> wrong_direction_dict;
    std::list<int> stations;
    int rem_duration{0};
    int anim_duration;
    int timer_duration;
    int init_time{0};

public slots:
    void start_this();

private:
    int pause{1000};
    bool end_me{false};

private slots:
    void move();

signals:
    void delete_me(int pos);

};

#endif // PATH_H
