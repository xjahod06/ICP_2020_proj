#include "progress_bar.h"
#include <QDebug>
#include "custom_line.h"
#include "path.h"

progress_bar::progress_bar(QObject *parent) :
    QGraphicsScene(parent)
{

    qDebug() << m_width;
    st_dict[0] = new custom_line(def_road_color);
    st_dict[0]->setLine(0,0,700,0);
    st_dict[0]->station = 0.8;
    addItem(st_dict[0]);
    qDebug() << height() << width();
}

void progress_bar::show_path(path *active_path)
{
    clear();
    int i = 0;
    qreal start = 0.0;
    qreal total_length = 0;
    foreach (auto road, active_path->st_dict) {
        total_length += road->line().length();
    }
    qDebug() << total_length << m_width << (m_width-30)/total_length;
    qreal correcter = (m_width-30)/total_length;
    foreach (auto road, active_path->st_dict) {
        qreal end = start+(road->line().length()*correcter);
        qDebug() << "start: " << start << "end" << end;
        st_dict[i] = new custom_line(active_path->m_vehicle->pen().color());
        st_dict[i]->setLine(start,0,start+road->line().length()*correcter,0);
        st_dict[i]->station = road->station;
        addItem(st_dict[i]);
        st_dict[i]->duration = road->duration;
        start = end;
    }
    qDebug() << width();
}

void progress_bar::reset_path()
{
    clear();
    qDebug() << "reseted";
}
