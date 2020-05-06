#include "menu_button.h"
#include <QDebug>
#include <QObject>

menu_button::menu_button(QObject *parent) :
    QAction(parent)
{

}

void menu_button::clicked()
{
    qDebug() << text();
    emit load_layout(path);
}
