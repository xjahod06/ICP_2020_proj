/** ICP Project 2020 transport map
 * @file path.h
 * @brief Objekt pro uchování a řízení spoje
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QLineF>
#include "custom_line.h"
#include "vehicle.h"

/// Objekt na uchování informací o spoji a pohybu vozidla po spoji
class path : public QObject
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit path(QObject *parent = nullptr);
    /**
     * @brief Najde cestu přes pole #st_dict
     * @details Porovná sousedící ulice a zjistí jestli některá z nich není špatně otočená, pokud je přidá ji do #wrong_direction_dict
     */
    void find_corr_way();
    QMap<int, custom_line*> st_dict; ///< Seznam ulic přes které spoj projíždí
    QList<int> wrong_direction_dict; ///< Seznam ulic které mají obrácený směr než je směr jízdy
    std::list<int> stations; ///< Seznam ulic, na kterých má spoj očekávat stanici
    vehicle *m_vehicle{nullptr}; ///< Vozidlo spoje
    QTimer *timer; ///< Interní časovač spoje pro animaci
    qreal speed{1.0}; ///< Rychlost spoje
    bool same{true}; ///< Proměnná na určení jestli se vozidlo pohybuje po stejné cestě
    bool forward{true}; ///< Směr pohybu vozidla po stoji
    qreal start{0.0}; ///< Relativní startovní souřadnice na ulici
    qreal end{1.0}; ///< Relativní cílová souřadnici na ulici
    int active_line{0}; ///< Pozici aktuální ulice ze seznamu #st_dict
    int prev_line{-1}; ///< Pozice přechozí pozice ulice
    int rem_duration{0}; ///< Zbývající čas na časovači
    int anim_duration; ///< Trvání aniamce
    int timer_duration; ///< Trvaní časovače
    bool active{true}; ///< Určí jestli je spoj aktivní
    int start_min{0}; ///< Minuta ve které spoj vyrazil
    int start_hour{0}; ///< Hodiny ve kterou spoj vyrazil
    bool end_me{false}; ///< Detekce ukončení spoje
    bool station_in_timer{false}; ///< Proměnná určující zda-li je spoj ve stanici či nikoliv
    int pause{1000}; ///< Pauza spoje na stanici

private:
    /**
     * @brief Vrátí silnici po vizuální stránce do základního stavu
     */
    void reset_colors();
    /**
     * @brief Zjistí jestli jsou 2 linie spojené
     * @param l1 Linie 1
     * @param l2 Linie 2
     * @return Vrátí, kterou z ulic je potřeba otočit
     */
    int is_connected(QLineF l1,QLineF l2);
    /**
     * @brief Obrátí startovní a konečný bod linie
     * @param line Linie na obrácení
     * @return Linie s obráceným směrem
     */
    QLineF reverse_line(QLineF line);

private slots:
    /**
     * @brief Řízení pohybu vozidla po spoji
     * @details Funkce kontroluje začáteční a koncovou relativní souřadnici spoje na ulici, kontroluje pohyb vozidla po ulici a následné stavení ve stanici.
     */
    void move();

signals:

};

#endif // PATH_H
