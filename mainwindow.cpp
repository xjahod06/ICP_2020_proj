#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

<<<<<<< Updated upstream
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));
=======
    //connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));

    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::lcd_up);
    //connect()
>>>>>>> Stashed changes
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< Updated upstream
=======
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->buttons();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        {
            //emit mouseWheelZoom(true);
            qDebug() << "zoom in";
            ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()+ui->zoom_slider->singleStep());
        }
        else
        {
            //emit mouseWheelZoom(false);
            qDebug() << "zoom out";
            ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()-ui->zoom_slider->singleStep());
        }
}

/*
void MainWindow::lcd_up()
{
    auto org = ui->lcdNumber->value();
    qDebug() << "value: " << org;
    ui->lcdNumber->display(org+10);
    ui->horizontalSlider->setSliderPosition(org+10);

}
*/
>>>>>>> Stashed changes
