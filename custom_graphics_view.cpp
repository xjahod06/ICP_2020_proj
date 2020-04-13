#include "custom_graphics_view.h"
#include <QBoxLayout>
#include "mainwindow.h"

custom_graphics_view::custom_graphics_view(QWidget *parent) :
    QGraphicsView(parent)
{
    auto horizontalLayout = new QHBoxLayout;
    viewport()->setLayout(horizontalLayout);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setSpacing(6);

    slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    slider->setValue(50);
    slider->setMinimum(25);
    slider->setMaximum(150);
    slider->setSliderPosition(50);
    //buttonPlus->setText("+");
    //buttonMinus->setText("-");
    verticalLayout->addWidget(slider);
    verticalLayout->addWidget(buttonPlus);
    verticalLayout->addWidget(buttonMinus);
    verticalLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

    horizontalLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    horizontalLayout->addItem(verticalLayout);

}
