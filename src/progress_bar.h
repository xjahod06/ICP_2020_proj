/** ICP Project 2020 transport map
 * @file progress_bar.h
 * @brief Objekt grafické scény pro vykreslení průběhu cesty spoje
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QGraphicsScene>
#include <QMap>
#include "custom_line.h"
#include "path.h"

/// Simulace spoje na alternativní cestě @see path
class progress_bar : public QGraphicsScene
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit progress_bar(QObject *parent = nullptr);
    int m_width; ///< Šířka okna
    vehicle *m_vehicle{nullptr}; ///< Vozidlo pro zobrazení relativní polohy vozidla
    QTimer **m_timer; ///< Ukazatel na ukazatel vybrané cesty
    qreal *speed; ///< Rychlost pohybu po cestě
    bool same; ///< Proměnná na určení jestli se vozidlo pohybuje po stejné cestě
    bool forward; ///< Směr pohybu vozidla po lince
    qreal start; ///< Relativní startovní souřadnice na ulici
    qreal end; ///< Relativní cílová souřadnici na ulici
    int active_line; ///< Pozice aktuální ulice ze seznamu #st_dict
    int prev_line; ///< Pozice předchozí pozice ulice

public slots:
    /**
     * @brief Synchronizuje svůj čas s hlavními hodinami
     * @param hour Hodiny
     * @param min Minuty
     * @see clock
     */
    void sync_self_clock(int hour, int min);
    /**
     * @brief Přijatý spoj pro vizualizaci
     * @param active_path Ukazatel na spoj pro vizualizace
     * @details Zkopíruje si důležité informace z vybraného spoje a následně vybraný spoj zobrazí na grafickou svcenu ve spodní části obrazovky
     */
    void show_path(path *active_path);
    /**
     * @brief Odstraní vybranou cestu z grafické scény
     */
    void reset_path();

private:
    /**
     * @brief Počet milisekund přepíše na čas
     * @param both Počet milisekund ke konverzi
     * @return Čas ve formátu "HH:MM"
     */
    QString convert_to_time(qreal both);
    /**
    * @brief Generuje výstupní tvar času
    * @param min Minuty formátu
    * @param hour Hodiny formátu
    * @return Časový formát ve tvaru "HH:MM"
    * @see clock
    */
    QString convert_time(int min, int hour);
    /**
     * @brief Vypočítá milisekundy z hodin a minut
     * @param hour Hodiny
     * @param min Minuty
     * @return Počet ms přepočtených z hodin a minut
     */
    int time_to_ms(int hour, int min);
    /**
     * @brief Vypočítá zpoždění a čas ke každé stanici na alternativní ceste
     * @param forward Směr vozidla na cestě
     */
    void delay_to_station(bool forward);
    QMap<int, custom_line*> st_dict; ///< Seznam ulic na alternativní ceste
    std::list<int> stations; ///< Seznam stanic na cestě
    QColor def_road_color{Qt::darkGray}; ///< Barva ulic
    int pause{1000}; ///< Pauza ve stanici
    path *progress_path; ///< Simulovaný spoj
    bool m_connected{false}; ///< Proměnná na určení připojení spoje
    int m_minute; ///< Interní minuty
    int m_hour; ///< Interní hodiny
    int def_minute{0}; ///< Minuty pro výpočet času na stanicích
    int def_hour{0}; ///< Hodiny pro výpočet času na stanicích
    bool new_line{false}; ///< Zjistění obrácení spoje
    int total_path_duration{0}; ///< Čas celé alternativní cesty spoje
    bool end_of_road{false}; ///< Proměnná na zjistění ukončení spoje

private slots:
    /**
     * @brief Pohyb spoje na alternativní cestě
     * @see move
     */
    void launch();

signals:

};

#endif // PROGRESS_BAR_H
