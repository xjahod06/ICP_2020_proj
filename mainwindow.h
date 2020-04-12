#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

/*
private slots:
    void lcd_up();
*/

private:
    void init_scene();
    void zoom_in();
    void zoom_out();
    void zoom_slide(int val);

    Ui::MainWindow *ui;

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

};
#endif // MAINWINDOW_H
