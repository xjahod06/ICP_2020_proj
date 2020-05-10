/** ICP Project 2020 transport map
 * @file path.h
 * @brief object pro uchovani a rizeni spoje hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QLineF>
#include "custom_line.h"
#include "vehicle.h"

class path : public QObject
{
    Q_OBJECT
public:
    /// konstruktor
    explicit path(QObject *parent = nullptr);
    /**
     * @brief najde cestu přes pole #st_dict
     * @details porovná sousedící ulice a zjistí jestli některá z nich není špatně otočená, pokud je přidá ji do #wrong_direction_dict
     */
    void find_corr_way();
    QMap<int, custom_line*> st_dict; ///< seznam ulic přes které spoj projíždí
    QList<int> wrong_direction_dict; ///< seznam ulic které mají obrácený smět než je směr jízdy
    std::list<int> stations; ///< seznam ulic, na kterých má spoj očekávat stanici
    vehicle *m_vehicle{nullptr}; ///< vozidlo spoje
    QTimer *timer; ///< interní časovač spoje pro animaci
    qreal speed{1.0}; ///< rychlost spoje
    bool same{true}; ///< proměnná na určení jestli se vozidlo pohybuje po stejné cestě
    bool forward{true}; ///< směr pohybu vozidla po stoji
    qreal start{0.0}; ///< relativní startovní souřadnice na ulici
    qreal end{1.0}; ///< relativní cílová souřadnici na ulici
    int active_line{0}; ///< pozici aktuální ulice ze seznamu #st_dict
    int prev_line{-1}; ///< pozice přechozí pozice ulice
    int rem_duration{0}; ///< zbývající čas na časovači
    int anim_duration; ///< trvani aniamce
    int timer_duration; ///< trvaní časovače
    bool active{true}; ///< určí jestli je spoj aktivní
    int start_min{0}; ///< minuta ve které spoj vyrazil
    int start_hour{0}; ///< hodiny ve kterou spoj vyrazil
    bool end_me{false}; ///< detekce ukončení spoje
    bool station_in_timer{false}; ///< proměnná na určení jestli je spoj ve stanici či nikoliv
    int pause{1000}; ///< pauza spoje na stanici

private:
    /**
     * @brief vrátí silnici po vizualni strance do zakladniho stavu
     */
    void reset_colors();
    /**
     * @brief zjistí jestli jsou 2 linie spojené
     * @param l1 linie 1
     * @param l2 linie 2
     * @return vrati které z ulic se musí otočit
     */
    int is_connected(QLineF l1,QLineF l2);
    /**
     * @brief obrati startovni a konečný bod linie
     * @param line linie na obrácení
     * @return linie s obrácenným směrem
     */
    QLineF reverse_line(QLineF line);

private slots:
    /**
     * @brief řízení pohybu vozidla po spoji
     * @details Funkce kontroluje začíteční a koncovou relativní souřadnici spoje na ulici, kontroluje pohyb vozidla po ulici a následné stavení ve stanici.
     */
    void move();

signals:

};

#endif // PATH_H
