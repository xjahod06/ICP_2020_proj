/** ICP Project 2020 transport map
 * @file progress_bar.h
 * @brief graficka scena pro vykresleni prubehu cesty spoje hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QGraphicsScene>
#include <QMap>
#include "custom_line.h"
#include "path.h"

/// simulace spoje na alternativní cestě @see path
class progress_bar : public QGraphicsScene
{
    Q_OBJECT
public:
    /// konstruktor
    explicit progress_bar(QObject *parent = nullptr);
    int m_width; ///< šířka okna
    vehicle *m_vehicle{nullptr}; ///< vozidlo pro zobrazení relativní polohy vozidla
    QTimer **m_timer; ///< ukazatel na ukazatel vybrané cesty
    qreal *speed; ///< rychlost pohybu po ceste
    bool same; ///< proměnná na určení jestli se vozidlo pohybuje po stejné cestě
    bool forward; ///< směr pohybu vozidla po stoji
    qreal start; ///< relativní startovní souřadnice na ulici
    qreal end; ///< relativní cílová souřadnici na ulici
    int active_line; ///< pozici aktuální ulice ze seznamu #st_dict
    int prev_line; ///< pozice přechozí pozice ulice

public slots:
    /**
     * @brief synchronizuje svuj čas s hlavními hodinami
     * @param hour hodiny
     * @param min minuty
     * @see clock
     */
    void sync_self_clock(int hour, int min);
    /**
     * @brief přijatý spoj pro vizualizaci
     * @param active_path ukazatel na spoj pro vizualizace
     * @details Zkopíruje si důležité informace z vybraného spoje a následně jej zobrazí na grafickou svcenu ve spední části obrazovky
     */
    void show_path(path *active_path);
    /**
     * @brief odstraní vybranou cestu z grafické scény
     */
    void reset_path();

private:
    /**
     * @brief počet ms přepíše na čas
     * @param both počet ms ke konvezi
     * @return čas ve formátu "hh:mm"
     */
    QString convert_to_time(qreal both);
    /**
    * @brief generuje výstupní tvar času
    * @param min minuty formatu
    * @param hour hodiny formatu
    * @return časový formát ve tvaru "hh:mm"
    * @see clock
    */
    QString convert_time(int min, int hour);
    /**
     * @brief vypocita ms z hodin a minut
     * @param hour hodiny
     * @param min minuty
     * @return počet ms přepočteny z hodin a minut
     */
    int time_to_ms(int hour, int min);
    /**
     * @brief vypočítá zpoždění a čas ke každé stanici na alternativní ceste
     * @param forward směr vozidla na cestě
     */
    void delay_to_station(bool forward);
    QMap<int, custom_line*> st_dict; ///< seznam ulic na alternativní ceste
    std::list<int> stations; ///< seznam stanic na cestě
    QColor def_road_color{Qt::darkGray}; ///< barva ulic
    int pause{1000}; ///< pauza ve stanici
    path *progress_path; ///< simulovaný spoj
    bool m_connected{false}; ///< proměnná na určení připojení spoje
    int m_minute; ///< interní minuty
    int m_hour; ///< interní hodiny
    int def_minute{0}; ///< minuty pro výpočet času na stanicích
    int def_hour{0}; ///< hodiny pro výpočet času na stanicích
    bool new_line{false}; ///< zjistění obrácení spoje
    int total_path_duration{0}; ///< čas celé alternativní cesty spoje
    bool end_of_road{false}; ///< proměnná na zjistění ukončneí spoje

private slots:
    /**
     * @brief pohyb spoje na alternativní cestě
     * @see move
     */
    void launch();

signals:

};

#endif // PROGRESS_BAR_H
