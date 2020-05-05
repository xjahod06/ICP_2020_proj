#include "custom_graphics_view.h"
#include <QBoxLayout>
#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QString>
#include "clock.h"
#include <QGraphicsItem>

custom_graphics_view::custom_graphics_view(QWidget *parent) :
    QGraphicsView(parent)
{

}

void custom_graphics_view::program_rdy_scene()
{
    buttonPlus = new QPushButton(this);
    buttonMinus = new QPushButton(this);
    lcd_timer = new class clock(this);
    slider = new QSlider(this);

    auto horizontalLayout = new QHBoxLayout;
    viewport()->setLayout(horizontalLayout);

    auto verticalLayout_lcd = new QHBoxLayout;
    verticalLayout_lcd->setSpacing(6);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setSpacing(6);

    slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    slider->setValue(50);
    slider->setMinimum(25);
    slider->setMaximum(150);
    slider->setSliderPosition(50);
    //buttonPlus->setText("+");
    //buttonMinus->setText("-");

    verticalLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
    verticalLayout->addWidget(slider);
    verticalLayout->addWidget(buttonPlus);
    verticalLayout->addWidget(buttonMinus);


    verticalLayout_lcd->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding));
    verticalLayout_lcd->addWidget(lcd_timer);

    horizontalLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    horizontalLayout->addItem(verticalLayout);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void custom_graphics_view::startup_scene()
{

}
