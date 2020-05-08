#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QToolButton>
#include "graphic_scene.h"
#include "custom_graphics_view.h"
#include "progress_bar.h"
#include "clock.h"
#include <fstream>
#include <QDir>
#include "menu_button.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->view->program_rdy_scene();

    init_scene();

    connect(ui->view->buttonPlus, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->view->buttonMinus, &QPushButton::clicked, this, &MainWindow::zoom_out);
    connect(ui->view->slider, &QSlider::valueChanged, this, &MainWindow::zoom_slide);
    connect(ui->traffic_level_up, &QPushButton::clicked, this, &MainWindow::inc_traffic_on_road);
    connect(ui->traffic_level_down, &QPushButton::clicked, this, &MainWindow::dec_traffic_on_road);

    //connect(ui->close_road, &QPushButton::clicked, this, &MainWindow::close_active_road);

    //connect(this, &QMainWindow::, this, &MainWindow::resized);
    parser = new file_parser(this,"../ICP_2020_proj/Example/welcome.txt");
    connect(parser, &file_parser::create_street, scene, &graphic_scene::create_street);
    connect(parser, &file_parser::create_label_text, scene, &graphic_scene::create_text);
    parser->parse_start();
    //ui->view->lcd_timer->check_the_start_timetables();
    //ui->view->lcd_timer->timer->start();

    QDir directory("../ICP_2020_proj/Example");
    QStringList list = directory.entryList(QStringList(),QDir::Files);
    qDebug() << directory << list;
    auto filemenu = ui->menubar->addMenu("examples");
    foreach (auto file_name, list) {
        menu_button *map_layout = new menu_button(filemenu);
        filemenu->addAction(map_layout );
        map_layout ->setText(file_name);
        connect(map_layout ,&menu_button::triggered, map_layout , &menu_button::clicked);
        connect(map_layout ,&menu_button::load_layout, this, &MainWindow::load_layout);
        map_layout ->path = directory.filePath(file_name);
    }

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   progress_scene->m_width = width();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init_scene()
{
    scene = new graphic_scene(ui->view);
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);

    progress_scene = new progress_bar(ui->progress_bar);
    ui->progress_bar->setScene(progress_scene);
    ui->progress_bar->setRenderHint(QPainter::Antialiasing);
    ui->progress_bar->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    progress_scene->m_width = width();

    connect(ui->speedSlider, &QSlider::valueChanged, scene, &graphic_scene::speed_change);
    connect(ui->speedSlider, &QSlider::valueChanged, ui->view->lcd_timer, &clock::speed_change);

    connect(ui->reset_timer_button, &QPushButton::clicked, ui->view->lcd_timer, &clock::reset_time);
    connect(ui->reset_timer_button, &QPushButton::clicked, scene, &graphic_scene::timer_reset);
    connect(scene, &graphic_scene::reseted, ui->view->lcd_timer, &clock::check_the_start_timetables);

    connect(ui->stop_timer_button, &QPushButton::clicked, this, &MainWindow::toggle_stop_button);
    connect(ui->stop_timer_button, &QPushButton::clicked, ui->view->lcd_timer, &clock::toggle_timer);
    connect(ui->stop_timer_button, &QPushButton::clicked, scene, &graphic_scene::toggle_timers);

    connect(scene, &graphic_scene::circle_clicked, progress_scene, &progress_bar::show_path);
    connect(scene, &graphic_scene::circle_unclicked, progress_scene, &progress_bar::reset_path);

    connect(ui->view->lcd_timer, &clock::propagade_clock, progress_scene, &progress_bar::sync_self_clock);
    connect(ui->view->lcd_timer, &clock::start_new_line, scene, &graphic_scene::generate_new_connection);

    connect(scene, &graphic_scene::road_clicked, this, &MainWindow::set_active_road);

}

void MainWindow::zoom_in()
{
    ui->view->slider->setSliderPosition(ui->view->slider->value()*1.25);
}

void MainWindow::zoom_out()
{
    ui->view->slider->setSliderPosition(ui->view->slider->value()/1.25);
}

void MainWindow::zoom_slide(int val)
{
    auto org = ui->view->transform();
    qreal scale = val/50.0;
    ui->view->setTransform(QTransform(scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}

void MainWindow::toggle_stop_button()
{
    ui->stop_timer_button->text() == "stop timers" ? ui->stop_timer_button->setText("start timers") : ui->stop_timer_button->setText("stop timers");
}

void MainWindow::inc_traffic_on_road()
{
    if(active_line != nullptr){
        active_line->inc_traffic();
        qDebug() << active_line->pos << active_line->traffic_level;
        QString lvl;
        ui->traffic_level_text->setText("Traffic level "+lvl.setNum(active_line->traffic_level));
    }
}

void MainWindow::dec_traffic_on_road()
{
    if(active_line != nullptr){
        active_line->dec_traffic();
        qDebug() << active_line->pos << active_line->traffic_level;
        QString lvl;
        ui->traffic_level_text->setText("Traffic level "+lvl.setNum(active_line->traffic_level));
    }
}

void MainWindow::close_active_road()
{
    if(active_line != nullptr){
        active_line->closed == true  ? qDebug() << active_line->pos << "opened" : qDebug() << active_line->pos << "closed";
        active_line->closed == true  ? active_line->closed = false : active_line->closed = true;
        active_line->closed == false ? ui->close_road->setText("close road") : ui->close_road->setText("open road");
        scene->line_selecting_for_close == false ? scene->line_selecting_for_close = true : scene->line_selecting_for_close = false;

    }
}

void MainWindow::load_layout(QString name)
{
    scene->reset_scene();
    ui->view->lcd_timer->reset_click();
    //ui->menubar->clear();
    if(parser != nullptr){
        parser->disconnect();
        delete(parser);
    }
    parser = new file_parser(this,name);
    connect(parser, &file_parser::create_street, scene, &graphic_scene::create_street);
    connect(parser, &file_parser::create_station, scene, &graphic_scene::create_station);
    connect(parser, &file_parser::create_route, scene, &graphic_scene::create_route);
    connect(parser, &file_parser::create_timetable, ui->view->lcd_timer, &clock::add_timetable);
    connect(parser, &file_parser::create_label_text, scene, &graphic_scene::create_text);
    parser->parse_start();
    ui->view->lcd_timer->check_the_start_timetables();
}

void MainWindow::set_active_road(custom_line *road)
{
    active_line = road;
    if(active_line != nullptr){
        QString lvl;
        ui->traffic_level_text->setText("Traffic level "+lvl.setNum(active_line->traffic_level));
    }else{
        ui->traffic_level_text->setText("Traffic level");
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
            ui->view->slider->setSliderPosition(ui->view->slider->value()+ui->view->slider->singleStep());
        }
        else{
            ui->view->slider->setSliderPosition(ui->view->slider->value()-ui->view->slider->singleStep());
        }
}

