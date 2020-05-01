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
    bool line_selecting_for_close{false};
    QMap<int, path*> path_dict;
    void generate_new_connection(int pos);

public slots:
    void speed_change(int val);
    void timer_reset();
    void toggle_timers();

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
    bool line_subsequent(QLineF l1, QLineF l2);

private slots:
    void start_all_paths();
    void delete_path(int pos);

signals:
    void circle_clicked(path *path);
    void circle_unclicked();
    void road_clicked(custom_line *road);
};

#endif // GRAPHIC_SCENE_H
