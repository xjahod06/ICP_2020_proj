#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <QObject>
#include <QPointF>
#include <QList>
#include <QColor>

class file_parser : public QObject
{
    Q_OBJECT
public:
    explicit file_parser(QObject *parent = nullptr,QString file_name = NULL);
    void parse_start();

private:
    QString m_file_name;
    void process_line(QString line);
    void process_street(QStringList list);
    QPointF get_point_from_string(QString point);
    void process_station(QStringList list);
    void process_route(QStringList list);
    QList<int> get_list_from_string(QStringList list);
    void process_timetable(QStringList list);
    void split_hour_and_minute_from_string(int *hour, int *min, QString string);
    void process_text(QStringList list);

signals:
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    void create_station(int street_id,qreal position);
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    void create_timetable(int route_id,int start_hour,int start_min,int end_hour,int end_min,int interval);
    void create_label_text(QString content,QPointF point,int font_size);
};

#endif // FILE_PARSER_H
