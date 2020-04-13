#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H

#include <QGraphicsScene>
#include "custom_line.h"

class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphic_scene(QObject *parent = nullptr);

private:
    QMap<int, custom_line*> st_dict;
    QTimer *timer;

private slots:
    void line();

signals:

};

#endif // GRAPHIC_SCENE_H
