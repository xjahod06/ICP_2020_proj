/** ICP Project 2020 transport map
 * @file mainwindow.h
 * @brief hlavní okno programu hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "progress_bar.h"
#include "custom_line.h"
#include "graphic_scene.h"
#include "file_parser.h"
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void zoom_in();
    void zoom_out();
    void zoom_slide(int val);
    void toggle_stop_button();
    void inc_traffic_on_road();
    void dec_traffic_on_road();
    void close_active_road();
    void load_layout(QString name);
    void browse();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void set_active_road(custom_line *road);

private:
    void init_scene();
    progress_bar *progress_scene;
    graphic_scene *scene;
    Ui::MainWindow *ui;
    custom_line *active_line{nullptr};
    file_parser *parser{nullptr};
    QMenu *layouts;

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

};
#endif // MAINWINDOW_H
