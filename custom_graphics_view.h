#ifndef CUSTOM_GRAPHICS_VIEW_H
#define CUSTOM_GRAPHICS_VIEW_H

#include <QGraphicsView>

#include <QSlider>
#include <QPushButton>
#include <QLCDNumber>
#include "clock.h"


class custom_graphics_view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit custom_graphics_view(QWidget *parent = nullptr);

public:
    QPushButton *buttonPlus{new QPushButton(this)};
    QPushButton *buttonMinus{new QPushButton(this)};
    class clock *lcd_timer{new class clock(this)};
    QSlider *slider{new QSlider(this)};

signals:

};

#endif // CUSTOM_GRAPHICS_VIEW_H
