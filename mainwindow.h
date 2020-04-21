#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "progress_bar.h"
#include "custom_line.h"

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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void set_active_road(custom_line *road);

private:
    void init_scene();
    progress_bar *progress_scene;
    Ui::MainWindow *ui;
    custom_line *active_line{nullptr};

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

};
#endif // MAINWINDOW_H
