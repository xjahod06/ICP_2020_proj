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
    /// konstruktor
    explicit menu_button(QObject *parent = nullptr);
    QString path; ///< cesta k souboru s daty

public slots:
    /**
     * @brief vyslání signálu #load_layout s cestou k soubrou
     */
    void clicked();

signals:
    /**
     * @brief propagace cesty k generování mapy
     * @param name cesta k souboru
     */
    void load_layout(QString name);
};

#endif // MENU_BUTTON_H
