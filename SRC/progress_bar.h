/** ICP Project 2020 transport map
 * @file progress_bar.h
 * @brief graficka scena pro vykresleni prubehu cesty spoje hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
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
    int pause{1000};
    path *progress_path;
    bool m_connected{false};
    int m_minute;
    int m_hour;
    int def_minute{0};
    int def_hour{0};
    bool new_line{false};
    QString convert_to_time(qreal both);
    QString convert_time(int min, int hour);
    int time_to_ms(int hour, int min);
    void delay_to_station(bool forward);
    int total_path_duration{0};
    std::list<int> stations;
    bool end_of_road{false};

private slots:
    void launch();

signals:

};

#endif // PROGRESS_BAR_H
