/** ICP Project 2020 transport map
 * @file clock.h
 * @brief Objekt na řízení hodin programu
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */

#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>
#include "timetable.h"
#include <QMap>

/// Objekt uchovávající aktuální čas uvnitř programu
class clock : public QLCDNumber
{
    Q_OBJECT
public:
    /**
    * @brief Konstruktor objektu
    */
    explicit clock(QWidget *parent = nullptr);
    /**
    * @brief Změní rychlost běhu hodin
    * @param val Hodnota rychlostního koeficientu z posuvníku
    */
    void speed_change(int val);
    /**
    * @brief Generuje výstupní tvar času
    * @param min Minuty formátu
    * @param hour Hodiny formátu
    * @return Časový formát ve tvaru "hh:mm"
    */
    QString convert_time(int min, int hour);
    /**
    * @brief Obnoví hodiny do výchozí hodnoty
    */
    void reset_time();
    QMap<int, timetable*> timetables; ///< Pole pro uchovaní jízdních řádů linek
    QTimer *timer;  ///< Časovač pro posun v čase
    int minute{0}; ///< Minuty
    int hour{0}; ///< Hodiny
    QString min_string; ///< Minuty jako řetězec
    QString hour_string; ///< Hodiny jako řetězec
    qreal speed{1.0}; ///< Rychlost času

public slots:
    /// Kontrola počátečních jízdních řádů (start "00:00") a spuštění hodin
    void check_the_start_timetables();
    /// Přepíná stav časovače na zapnuto/vypnuto (pauza)
    void toggle_timer();
    /**
    * @brief Přidá další jízdní řád
    * @param ID ID linky, ke které se jízdní řád vztahuje
    * @param start_hour Hodina, ve kterou začne spoj být aktivní
    * @param start_min Minuta, ve kterou začne spoj být aktivní
    * @param end_hour Hodina, ve kterou může spoj naposledy vyjet
    * @param end_min Minuta, ve kterou může spoj naposledy vyjet
    * @param interval Časový interval v sekundách, podle kterého se vypouští další spoje
    * @details Funkce vygeneruje nový jízdní řád linky a ten uloží do pole @link timetables @endlink
    */
    void add_timetable(int ID,int start_hour, int start_min, int end_hour, int end_min, int interval);
    /// Resetuje pole @see timetables
    void reset_timetables();

private:
    QString separator{":"}; ///< oOddělovač hodin a minut při zobrazení

private slots:
    /**
    * @brief pPosune čas o jednu minutu
    * @details Zvýší hodnotu minute, pokud je hodnota rovna 60 zvýší hour a minute nastaví na 0. Tento čas poté vyšle do programu signálem @link propagade_clock @endlink.
    * Následně zjistí jestli se zvýšením aktuálního času neaktivuje některý jízdní řád a případně z něj vysláním signálu start_new_line vytvoří nový spoj na mapě.
    */
    void time_up();

signals:
    /**
    * @brief Propraguje aktuální čas do programu
    * @param hour Hodiny
    * @param minute Minuty
    */
    void propagade_clock(int hour, int minute);
    /**
    * @brief Vyšle signál o vytvoření nového spoje
    * @param pos ID linky, která se má vytvořit (pozice v seznamu)
    * @param min Minuty
    * @param hour Hodiny
    */
    void start_new_line(int pos, int min, int hour);

};

#endif // CLOCK_H
