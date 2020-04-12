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
<<<<<<< Updated upstream

=======
/*
private slots:
    void lcd_up();
*/
>>>>>>> Stashed changes
private:
    Ui::MainWindow *ui;

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

};
#endif // MAINWINDOW_H
