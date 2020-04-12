#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::lcd_up);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lcd_up()
{
    auto org = ui->lcdNumber->value();
    qDebug() << "value: " << org;
    ui->lcdNumber->display(org+10);
    ui->horizontalSlider->setSliderPosition(org+10);

}

