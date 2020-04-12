#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsScene>
#include "graphic_scene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_scene();

    connect(ui->zoom_in_button, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->zoom_out_button, &QPushButton::clicked, this, &MainWindow::zoom_out);

    connect(ui->zoom_slider, &QSlider::valueChanged, this, &MainWindow::zoom_slide);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_scene()
{
    auto scene = new graphic_scene(ui->view);
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::zoom_in()
{
    //ui->view->scale(1.25,1.25);
    ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()*1.25);
}

void MainWindow::zoom_out()
{
    //ui->view->scale(0.8,0.8);
    ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()/1.25);
}

void MainWindow::zoom_slide(int val)
{
    auto org = ui->view->transform();
    qreal scale = val/50.0;
    ui->view->setTransform(QTransform(scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        {
            //qDebug() << "zoom in" << ui->zoom_slider->value();
            ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()+ui->zoom_slider->singleStep());
        }
        else
        {

            //qDebug() << "zoom out" << ui->zoom_slider->value();
            ui->zoom_slider->setSliderPosition(ui->zoom_slider->value()-ui->zoom_slider->singleStep());
        }
}
