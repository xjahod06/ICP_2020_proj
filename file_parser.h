#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <QObject>
#include <QPointF>

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

signals:
    void create_street(int street_id,QPointF start_p,QPointF end_p);
};

#endif // FILE_PARSER_H
