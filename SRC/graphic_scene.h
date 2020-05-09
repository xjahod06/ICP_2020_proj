#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include "custom_line.h"
#include "path.h"
#include "vehicle.h"

class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphic_scene(QObject *parent = nullptr);
    bool line_selecting_for_close{false};
    QMap<int, path*> path_dict;

public slots:
    void generate_new_connection(int pos,int min, int hour);
    void speed_change(int val);
    void timer_reset();
    void toggle_timers();
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    void create_station(int street_id,qreal position);
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    void reset_scene();
    void create_text(QString content,QPointF point,int font_size);

private:
    QMap<int, path*> defined_path;
    QMap<int, custom_line*> st_dict;
    QMap<int, vehicle*> vehicle_dict;
    qreal speed{1.0};
    bool change_rdy{true};
    void reset_click_on_lines(int pos);
    void check_clicked(int pos);
    QColor def_road_color{Qt::darkGray};
    void select_line(custom_line *road);
    void reset_line_selection(int pos);
    QMap<int, custom_line *> insert_into_map(QMap<int, custom_line*> *map, int index, custom_line* value);
    QMap<int, custom_line *> remove_from_map(QMap<int, custom_line*> *map, int index);
    int is_in_map(QMap<int, custom_line*> map, custom_line* value);
    QMap<int, custom_line *> alternate_route;
    custom_line *selected_line;
    bool line_subsequent(QLineF l1, QLineF l2, int *direction);
    QStringList print_street_id(QMap<int, custom_line*> map);

private slots:
    void start_all_paths();
    void delete_path(int pos);

signals:
    void circle_clicked(path *path);
    void circle_unclicked();
    void road_clicked(custom_line *road);
    void reseted();
};

#endif // GRAPHIC_SCENE_H
