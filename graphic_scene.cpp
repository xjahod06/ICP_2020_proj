#include "graphic_scene.h"
#include <QGraphicsItem>
#include "custom_line.h"

graphic_scene::graphic_scene(QObject *parent) :
    QGraphicsScene(parent)
{
    auto line = new custom_line();
    line->setLine(0,0,150,150);
    addItem(line);

    line = new custom_line(Qt::blue);
    line->setLine(0,50,100,150);
    addItem(line);


}
