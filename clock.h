#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>

class clock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit clock(QWidget *parent = nullptr);
    QTimer *timer;
    int minute{00};
    int hour{00};
    QString min_string;
    QString hour_string;
    qreal speed{1.0};
    void speed_change(int val);
    void reset_time();
    QString convert_time(int min, int hour);

private:
    QString separator{":"};

private slots:
    void time_up();

signals:
    void propagade_clock(int hour, int minute);

};

#endif // CLOCK_H
