#include "custom_graphics_view.h"
#include <QBoxLayout>
#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QString>

custom_graphics_view::custom_graphics_view(QWidget *parent) :
    QGraphicsView(parent)
{
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

    //lcd_timer->setSegmentStyle(QLCDNumber::Flat);
    //lcd_timer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lcd_timer->resize(150,60);
    lcd_timer->display("00:00");

    //qDebug() << lcd_timer->segmentStyle();

    verticalLayout_lcd->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding));
    verticalLayout_lcd->addWidget(lcd_timer);

    horizontalLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    //horizontalLayout->addItem(verticalLayout_lcd);
    horizontalLayout->addItem(verticalLayout);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

}
