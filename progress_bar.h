#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QGraphicsScene>
#include <QMap>
#include "custom_line.h"
#include "path.h"

class progress_bar : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit progress_bar(QObject *parent = nullptr);
    int m_width;
    vehicle *m_vehicle{nullptr};
    QTimer **m_timer;
    qreal *speed;
    bool same;
    bool forward;
    qreal start;
    qreal end;
    int active_line;
    int prev_line;
    void sync_self_clock(int hour, int min);

public slots:
    void show_path(path *active_path);
    void reset_path();

private:
    QMap<int, custom_line*> st_dict;
    QColor def_road_color{Qt::darkGray};
    int pause{750};
    path *progress_path;
    bool m_connected{false};
    int m_minute;
    int m_hour;
    QString convert_time(int min, int hour);

private slots:
    void launch();

signals:

};

#endif // PROGRESS_BAR_H
