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
    QPushButton *buttonPlus{nullptr};
    QPushButton *buttonMinus{nullptr};
    class clock *lcd_timer{nullptr};
    QSlider *slider{nullptr};
    void program_rdy_scene();
    void startup_scene();

private:

signals:

};

#endif // CUSTOM_GRAPHICS_VIEW_H
