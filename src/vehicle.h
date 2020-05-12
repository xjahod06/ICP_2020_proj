/** ICP Project 2020 transport map
 * @file vehicle.h
 * @brief Objekt vozidla na mapě
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QPen>
#include <QVariantAnimation>
#include <QGraphicsEllipseItem>

/// Objekt reprezentující vozidlo na mapě
class vehicle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit vehicle(QGraphicsItem *parent = nullptr);
    /**
     * @brief Změna souřadnice vozidla pro pohyb
     * @param paint_point Bod na ulici na kterém se má vozidlo vykreslit
     */
    void move_yourself_lazy_circle(QPointF paint_point);
    QPen m_pen{QPen({Qt::red},3)}; ///< Pero na uložení barvy vozidla
    int size{10}; ///< Velikost vozidla
    qreal position{0.0}; ///< Relativní pozice vozidla na ulici
    bool active{false}; ///< Detekce aktivity animace vozidla
    QVariantAnimation *anim{nullptr}; ///< Animace vozidla (řídí pohyb po ulici)
    int pos_in_dict; ///< Unikátní pozice vozidla v seznamech
    bool cliked{false}; ///< Určení jestli je vozidlo vybrané
    bool hide{false}; ///< Zakrytí vozidla na mapě

private:
    QPointF center; ///< Bod na kterém se vykresluje vozidlo

protected:
    /**
     * @brief Qt funkce, která detekuje kliknutí na objekt vozidla
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * @brief Qt funkce, která vykreslí objekt vozidla
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    /**
     * @brief Qt funkce, která vypočítá vykreslovací rámec objektu vozidla
     */
    virtual QRectF boundingRect() const override;

signals:
    /**
     * @brief Propagace kliknutí na objekt vozidla
     * @param pos Pozice vybraného objektu vozidla
     */
    void circle_clicked(int pos);

};

#endif // VEHICLE_H
