#include "file_parser.h"
#include <QFile>
#include <QDebug>
#include <QPointF>
#include <QDir>
#include <QList>
#include <QColor>

file_parser::file_parser(QObject *parent,QString file_name) : QObject(parent)
{
    m_file_name = file_name;
}

void file_parser::parse_start()
{
    QFile file(m_file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "some problems with" << m_file_name << QDir::currentPath();
    }

    QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            process_line(line);
        }
}

void file_parser::process_line(QString line)
{
    if(line.at(0) == '#'){
        return;
    }
    auto list = line.split('|');
    //qDebug() << list << list.at(0);
    if(list.at(0) == "street"){
        process_street(list);
    }else if(list.at(0) == "station"){
        process_station(list);
    }else if(list.at(0) == "route"){
        process_route(list);
    }else if(list.at(0) == "timetable"){
        process_timetable(list);
    }else if(list.at(0) == "text"){
        process_text(list);
    }else{
        qDebug() << "identifikator not recognised";
    }
}

void file_parser::process_street(QStringList list)
{
    int street_id;
    QPointF start_p;
    QPointF end_p;
    QString street_name;
    list.removeAt(0);
    street_id = list.at(0).toInt();
    start_p = get_point_from_string(list.at(1));
    end_p = get_point_from_string(list.at(2));

    if(list.count() == 4){
        street_name = list.at(3);
    }else{
        street_name = "";
    }

    emit create_street(street_id,start_p,end_p,street_name);
}

QPointF file_parser::get_point_from_string(QString point)
{
    auto list = point.split(',');
    return QPointF(list.at(0).toInt(),list.at(1).toInt());
}

void file_parser::process_station(QStringList list)
{
    int street_id;
    qreal percent_value;
    list.removeAt(0);
    street_id = list.at(0).toInt();
    percent_value = list.at(1).toFloat();
    emit create_station(street_id,percent_value);
}

void file_parser::process_route(QStringList list)
{
    int route_id;
    QList<int> streets;
    QList<int> stations;
    list.removeAt(0);
    route_id = list.at(0).toInt();
    streets = get_list_from_string(list.at(1).split(','));
    stations = get_list_from_string(list.at(2).split(','));
    QColor color(list.at(3));
    emit create_route(route_id,streets,stations,color);
}

QList<int> file_parser::get_list_from_string(QStringList list)
{
    QList<int> num_list;
    foreach (auto id, list) {
        num_list.push_back(id.toInt());
    }
    return num_list;
}

void file_parser::process_timetable(QStringList list)
{
    int route_id;
    int start_hour;
    int start_min;
    int end_hour;
    int end_min;
    int interval;
    list.removeAt(0);
    route_id = list.at(0).toInt();
    split_hour_and_minute_from_string(&start_hour,&start_min,list.at(1));
    split_hour_and_minute_from_string(&end_hour,&end_min,list.at(2));
    interval = list.at(3).toInt();
    emit create_timetable(route_id, start_hour, start_min, end_hour, end_min, interval);

}

void file_parser::split_hour_and_minute_from_string(int *hour, int *min, QString string)
{
    if(string == "-1"){
        *hour = -1;
        *min = -1;
    }else{
        auto list = string.split(":");
        *hour = list.at(0).toInt();
        *min = list.at(1).toInt();
    }
}

void file_parser::process_text(QStringList list)
{
    QString content;
    QPointF point;
    int font_size;
    list.removeAt(0);
    content = list.at(0);
    point = get_point_from_string(list.at(1));
    font_size = list.at(2).toInt();
    emit create_label_text(content,point,font_size);

}
