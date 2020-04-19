#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "progress_bar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void zoom_in();
    void zoom_out();
    void zoom_slide(int val);

private:
    void init_scene();
    progress_bar *progress_scene;
    Ui::MainWindow *ui;

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

};
#endif // MAINWINDOW_H
