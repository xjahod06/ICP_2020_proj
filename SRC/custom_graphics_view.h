/** ICP Project 2020 transport map
 * @file custom_graphics_view.h
 * @brief graphics view na definovani UI hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef CUSTOM_GRAPHICS_VIEW_H
#define CUSTOM_GRAPHICS_VIEW_H

#include <QGraphicsView>

#include <QSlider>
#include <QPushButton>
#include <QLCDNumber>
#include "clock.h"

///definice ui prvků které jsou přímo v okně mapy
class custom_graphics_view : public QGraphicsView
{
    Q_OBJECT
public:
    ///konstruktor
    explicit custom_graphics_view(QWidget *parent = nullptr);
    /**
    * @brief umístění základních objektu UI na scenu
    * @details funkce vygeneruje funkce pro zoom a ukazatel času, následně je rozdělí do několika layoutů, aby se zajistilo správné umístění i po změně velikosti okna
    */
    void program_rdy_scene();
    QPushButton *buttonPlus{nullptr}; ///< tlačítko na přiblížení pohledu
    QPushButton *buttonMinus{nullptr}; ///< tlačítko na oddálení pohledu
    class clock *lcd_timer{nullptr}; ///< ukazatel aktuálního času
    QSlider *slider{nullptr}; ///< slider pro přiblížení a oddálení

private:

signals:

};

#endif // CUSTOM_GRAPHICS_VIEW_H
