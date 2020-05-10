/** ICP Project 2020 transport map
 * @file menu_button.h
 * @brief tlacitka pro nacteni souboru hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QObject>
#include <QAction>
#include <QDir>

class menu_button : public QAction
{
    Q_OBJECT
public:
    explicit menu_button(QObject *parent = nullptr);
    QString path;

public slots:
    void clicked();

signals:
    void load_layout(QString name);
};

#endif // MENU_BUTTON_H
