/** ICP Project 2020 transport map
 * @file timetable.h
 * @brief jízdní řád spoje hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QObject>
/// uložení informací spoji
class timetable : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief constructor objektu
    */
    explicit timetable(QObject *parent = nullptr, int ID = -1, int s_hour = 0, int s_min = 0, int inter = 0, int e_hour = -1, int e_min = -1);
    int interval{1}; ///< interval v sekundách pro generování spojů
    int path_id{-1}; ///< ID linky které se daný jízdní řád týka
    int start_hour{0}; ///< hodina ve kterou začne spoj být aktivní
    int start_min{0}; ///< minuta ve kterou začne spoj být aktivní
    int end_hour{-1}; ///< hodina ve kterou může být vygenerován poslední spoj
    int end_min{-1}; ///< minuta ve kterou může být vygenerován poslední spoj
    bool active{false}; ///< určuje jesli spoj je nebo neni aktivní

signals:

};

#endif // TIMETABLE_H
