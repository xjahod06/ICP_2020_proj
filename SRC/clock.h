/** ICP Project 2020 transport map
 * @file clock.h
 * @brief object na řízení hodin programu hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */

#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>
#include "timetable.h"
#include <QMap>

/// objekt na uchovani aktualniho času programu
class clock : public QLCDNumber
{
    Q_OBJECT
public:
    /**
    */
    explicit clock(QWidget *parent = nullptr);
    /**
    * @brief změna rychlosti běhu hodin
    * @param val hodnota rychlostniho koeficientu ze slidebaru
    */
    void speed_change(int val);
    /**
    * @brief generuje výstupní tvar času
    * @param min minuty formatu
    * @param hour hodiny formatu
    * @return časový formát ve tvaru "hh:mm"
    */
    QString convert_time(int min, int hour);
    /**
    * @brief resetuje hodiny do zakladnich hodnot
    */
    void reset_time();
    QMap<int, timetable*> timetables; ///< pole pro uchovani jízdních řádů linek
    QTimer *timer;  ///< časovač pro posun v čase
    int minute{0}; ///< minuty
    int hour{0}; ///< hodiny
    QString min_string; ///< minuty jako string
    QString hour_string; ///< hodiny jako string
    qreal speed{1.0}; ///< rychlost času

public slots:
    /// kontrola počátečních jízdních řádů (start "00:00") a zapnutí počítání hodin
    void check_the_start_timetables();
    /// přepíná stav časovace na zapnuto/vypnuto (pauza)
    void toggle_timer();
    /**
    * @brief přidá další jízdní řád
    * @param ID id linky ke které se jízdní řád vztahuje
    * @param start_hour hodina ve kterou začne spoj být aktivní
    * @param start_min minuta ve kterou začne spoj být aktivní
    * @param end_hour hodina ve kterou může spoj naposledy vyjet
    * @param end_min minuta ve kterou může spoj naposledy vyjet
    * @param interval časový interval v sekundách podle kterého se vypouští další spoje
    * @details funkce vygeneruje nový jízdní řád s linkou a ten uloží do pole @link timetables @endlink
    */
    void add_timetable(int ID,int start_hour, int start_min, int end_hour, int end_min, int interval);
    /// vyresetuje pole @see timetables
    void reset_timetables();

private:
    QString separator{":"}; ///< oddělovač hodin a minut při zobrazení

private slots:
    /**
    * @brief posune čas o jednu minutu
    * @details Zvýší hodnotu minute, pokud je hodnota rovna 60 zvýší hour a minute nastaví na 0. Tento čas poté vyšle do programu signálem @link propagade_clock @endlink.
    * Následně zjistí jestli se zvýšením aktuálního času neaktivuje některý jízdní řád a případně z něj vysláním signálu start_new_line vytvoří nový spoj na mapě.
    */
    void time_up();

signals:
    /**
    * @brief zpropraguje aktuální čas do programu
    * @param hour hodiny
    * @param minute minuty
    */
    void propagade_clock(int hour, int minute);
    /**
    * @brief vyšle signál o vytvoření nového spoje
    * @param pos id linky která se má vytvořit (pozice v seznamu)
    * @param min minuty
    * @param hour hodiny
    */
    void start_new_line(int pos, int min, int hour);

};

#endif // CLOCK_H
