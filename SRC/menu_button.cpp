/** ICP Project 2020 transport map
 * @file menu_button.cpp
 * @brief tlacitka pro nacteni souboru
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
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
