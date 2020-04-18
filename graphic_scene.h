#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H

#include <QGraphicsScene>
#include "custom_line.h"
#include "path.h"
#include "vehicle.h"

class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphic_scene(QObject *parent = nullptr);

public slots:
    void speed_change(int val);

private:
    QMap<int, custom_line*> st_dict;
    QMap<int, path*> path_dict;
    QMap<int, vehicle*> vehicle_dict;
    qreal speed{1.0};
    bool change_rdy{true};
    void reset_click_on_lines(int pos);
    void check_clicked(int pos);

private slots:

signals:

};

#endif // GRAPHIC_SCENE_H
