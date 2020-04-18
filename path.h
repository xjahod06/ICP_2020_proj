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
    int a{0};

private:
    int active_line{0};
    bool forward{true};
    qreal start{0.0};
    qreal end{1.0};
    int pause{750};
    bool same{false};
    int prev_line{-1};

private slots:
    void move();

signals:

};

#endif // PATH_H
