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

public slots:
    void show_path(path *active_path);
    void reset_path();

private:
    QMap<int, custom_line*> st_dict;
    QColor def_road_color{Qt::darkGray};
    int pause{750};
    path *progress_path;

private slots:
    void launch();

signals:

};

#endif // PROGRESS_BAR_H
