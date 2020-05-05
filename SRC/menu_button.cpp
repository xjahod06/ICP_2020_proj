#include "menu_button.h"
#include <QDebug>

menu_button::menu_button(QWidget *parent) :
    QAction(parent)
{

}

void menu_button::clicked()
{
    qDebug() << text();
}
