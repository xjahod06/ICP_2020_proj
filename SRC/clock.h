#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>
#include "timetable.h"
#include <QMap>

class clock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit clock(QWidget *parent = nullptr);
    QTimer *timer;
    int minute{0};
    int hour{0};
    QString min_string;
    QString hour_string;
    qreal speed{1.0};
    void speed_change(int val);
    void reset_time();
    QString convert_time(int min, int hour);
    QMap<int, timetable*> timetables;
    void add_timetable(int ID,int start_hour, int start_min, int interval, int end_hour, int end_min);
    void check_the_start_timetables();

public slots:
    void toggle_timer();

private:
    QString separator{":"};

private slots:
    void time_up();

signals:
    void propagade_clock(int hour, int minute);
    void start_new_line(int pos, int min, int hour);

};

#endif // CLOCK_H
