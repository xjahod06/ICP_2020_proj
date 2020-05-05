#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QObject>
#include <QAction>
#include <QDir>

class menu_button : public QAction
{

public:
    explicit menu_button(QWidget *parent = nullptr);
    QString path;

public slots:
    void clicked();

signals:

};

#endif // MENU_BUTTON_H
