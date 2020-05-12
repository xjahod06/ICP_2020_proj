/** ICP Project 2020 transport map
 * @file timetable.h
 * @brief Objekt jízdního řádu spoje
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QObject>
/// Uložení informací o spoji
class timetable : public QObject
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit timetable(QObject *parent = nullptr, int ID = -1, int s_hour = 0, int s_min = 0, int inter = 0, int e_hour = -1, int e_min = -1);
    int interval{1}; ///< Interval v sekundách pro generování spojů
    int path_id{-1}; ///< ID linky, které se daný jízdní řád týka
    int start_hour{0}; ///< Hodina, ve kterou začne spoj být aktivní
    int start_min{0}; ///< Minuta, ve kterou začne spoj být aktivní
    int end_hour{-1}; ///< Hodina, ve kterou může být vygenerován poslední spoj
    int end_min{-1}; ///< Minuta, ve kterou může být vygenerován poslední spoj
    bool active{false}; ///< Určuje jestli spoj je nebo není aktivní

signals:

};

#endif // TIMETABLE_H
