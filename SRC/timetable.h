#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QObject>

class timetable : public QObject
{
    Q_OBJECT
public:
    explicit timetable(QObject *parent = nullptr, int ID = -1, int s_hour = 0, int s_min = 0, int inter = 0, int e_hour = -1, int e_min = -1);
    int interval{1}; //in sec
    int path_id{-1};
    int start_hour{0};
    int start_min{0};
    int end_hour{-1};
    int end_min{-1};
    bool active{false};

signals:

};

#endif // TIMETABLE_H
