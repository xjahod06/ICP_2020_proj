#include "file_parser.h"
#include <QFile>
#include <QDebug>
#include <QPointF>

file_parser::file_parser(QObject *parent,QString file_name) : QObject(parent)
{
    m_file_name = file_name;
}

void file_parser::parse_start()
{
    QFile file(m_file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            process_line(line);
        }
}

void file_parser::process_line(QString line)
{
    qDebug() << line;
    if(line.at(0) == '#'){
        return;
    }
    auto list = line.split('|');
    //qDebug() << list << list.at(0);
    if(list.at(0) == "street"){
        qDebug() << "street recognised";
        process_street(list);
    }else if(list.at(0) == ""){
        qDebug() << " recognised";
    }else{
        qDebug() << "identifikator not recognised";
    }
}

void file_parser::process_street(QStringList list)
{
    int street_id;
    QPointF start_p;
    QPointF end_p;
    list.removeAt(0);
    qDebug() << list;
    street_id = list.at(0).toInt();
    start_p = get_point_from_string(list.at(1));
    end_p = get_point_from_string(list.at(2));
    qDebug() << street_id << start_p << end_p;
    //emit create_street(0,QPointF(0,0),QPointF(-5,200));
    emit create_street(street_id,start_p,end_p);
    qDebug() << "emitted";
}

QPointF file_parser::get_point_from_string(QString point)
{
    auto list = point.split(',');
    return QPointF(list.at(0).toInt(),list.at(1).toInt());
}
