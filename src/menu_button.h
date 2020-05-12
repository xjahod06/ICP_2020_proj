/** ICP Project 2020 transport map
 * @file menu_button.h
 * @brief Objekt tlačítka pro načtení souboru
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QObject>
#include <QAction>
#include <QDir>

/// Tlačítko pro výběr map layoutu
class menu_button : public QAction
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit menu_button(QObject *parent = nullptr);
    QString path; ///< cesta k souboru s daty

public slots:
    /**
     * @brief Vyslání signálu #load_layout s cestou k soubrou
     */
    void clicked();

signals:
    /**
     * @brief Propagace cesty k generování mapy
     * @param name Cesta k souboru
     */
    void load_layout(QString name);
};

#endif // MENU_BUTTON_H
