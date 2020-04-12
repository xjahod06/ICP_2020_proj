#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H

#include <QGraphicsScene>

class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphic_scene(QObject *parent = nullptr);

signals:

};

#endif // GRAPHIC_SCENE_H
