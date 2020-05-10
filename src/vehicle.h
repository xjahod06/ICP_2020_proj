/** ICP Project 2020 transport map
 * @file vehicle.h
 * @brief vozidlo na mapě hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QPen>
#include <QVariantAnimation>
#include <QGraphicsEllipseItem>

class vehicle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    /// konstruktor
    explicit vehicle(QGraphicsItem *parent = nullptr);
    /**
     * @brief změna souřadnice vozidla pro pohyb
     * @param bod na ulici na kterém se má vozidlo vykreslit
     */
    void move_yourself_lazy_circle(QPointF paint_point);
    QPen m_pen{QPen({Qt::red},3)}; ///< pero na uložení barvy vozidla
    int size{10}; ///< velikost vozidla
    qreal position{0.0}; ///< relativní pozice vozidla na ulici
    bool active{false}; ///< detekce aktivity animace vozidla
    QVariantAnimation *anim{nullptr}; ///< animace vozidla (řídí pohyb po ulici)
    int pos_in_dict; ///< unikátní pozice vozidla v seznamech
    bool cliked{false}; ///< určení jestli je vozidlo vybrané
    bool hide{false}; ///< zakrytí vozidla na mapě

private:
    QPointF center; ///< bod na kterém se vykresluje vozidlo

protected:
    /**
     * @brief qt funkce na detekci kliknutí na vozidlo
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * @brief qt funkce na vykreslování vozidla
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    /**
     * @brief qt funkce na výpočet vykreslovacího rámce vozidla
     */
    virtual QRectF boundingRect() const override;

signals:
    /**
     * @brief propagace kliknutí na vozidlo
     * @param pos pozice vybraného vozidla
     */
    void circle_clicked(int pos);

};

#endif // VEHICLE_H
