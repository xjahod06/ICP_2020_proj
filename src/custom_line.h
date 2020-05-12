/** ICP Project 2020 transport map
 * @file custom_line.h
 * @brief Objekt ulice na mapě
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef CUSTOM_LINE_H
#define CUSTOM_LINE_H

#include <QGraphicsLineItem>
#include <QVariantAnimation>
#include <QTimer>
#include <QPen>
#include "vehicle.h"

/// Objekt pro zachování informace o dané ulici
class custom_line :public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit custom_line(QColor m_color = Qt::red, QGraphicsItem *parent = nullptr);
    /**
    * @brief Přidá vozidlo na ulici a uloží se do jeho animace
    * @pre Objekt vozidla nesmí být nullptr
    * @param new_vehicle Ukazatel na právě přidávané vozidlo
    * @param pos Unikátní pozice vozidla v seznamu
    * @details Funkce uloží ukazatel do pole @link vehicle_dict @endlink na pozici @param pos a následně mu vytvoří animaci,
    * tuto animaci spojí s funkcí @link test_anim @endlink, která poté pohybuje s vozidlem na mapě.
    */
    void add_vehicle(vehicle* new_vehicle,int pos);
    /**
    * @brief Odstraní vozidlo z ulice a odpojí jej od ní
    * @param pos Unikátní pozice vozidla v sezamu
    */
    void remove_vehicle(int pos);
    /**
    * @brief Nastaví dobu, po kterou se bude provádět animace na dané ulici
    */
    void set_anim();
    /**
    * @brief Zvýší úroveň provozu na dané cestě
    * @details Je voláno externě po zavolání fuknce @link inc_traffic_on_road @endlink a následně určí a případně omezí svoji úrověn dopravy (max 16),
    *  Následně podle dané úrovně dopravy zvýší odstín červené jakožto grafickou vizualizaci zpoždění na dané cestě.
    */
    void inc_traffic();
    /**
    * @brief Sníží úroveň provozu na dané cestě
    * @details Je voláno externě po zavolání fuknce @link dec_traffic_on_road @endlink a následně určí a případně omezí svoji úrověn dopravy (min 0),
    *  Následně podle dané úrovně dopravy sníží odstín červené jakožto grafickou vizualizaci zpoždění na dané cestě.
    *
    */
    void dec_traffic();
    QPen m_pen{QPen({Qt::darkGray},3)}; ///< Pero dané cesty, do kterého se v průběhu mohou ukládat barvy dané cesty
    QColor def_color; ///< Základní barvy silnice nastavená při inicializaci
    int duration{1000}; ///< Doba, po kterou se jede po dané cestě
    int delay{0}; ///< Zpozdění na dané cestě, počítá se podle úrovně dopravy
    qreal station{-1}; ///< Pozice stanice na cestě (-1 znamená že daná cesta nemá žádnou stanici)
    QMap<int, vehicle*> vehicle_dict; ///< Pole pro ukládání ukazatelů na vozidla, která se vyskytují na dané cestě
    QString station_time{""}; ///< Čas ve který má spoj dojet na stanici (využito pouze ve scéně @link progress_bar @endlink)
    QString station_delay{"00:00"}; ///< Čas zpoždění stanice (využito pouze ve scéně @link progress_bar @endlink)
    bool selected_in_path{false}; ///< Určuje jestli se dané ulice vyskytuje ve vybraném spoji pro vykreslování
    bool selected{false}; ///< Určuje jestli je daná cesta vybrána
    int pos; ///< Unikátní pozice v seznamech
    int traffic_level{0}; ///< Úrověn dopravy na dané cestě
    bool closed{false}; ///< Proměnná, která určuje jestli je ulice uzavřena nebo ne (nepodařilo se dokončit)
    QString name{""}; ///< Jméno dané ulice (může být prázdné)

protected:
    /// Qt funkce, díky které se dá detekovat kliknutí na cestu. Volá signál @link line_selected @endlink
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /**
    * @brief Qt funkce, která vykreslí linku
    * @details Zde se kontroluje jaké atributy jsou zadány a případně se upravuje vizuální stránka cesty (stanice, barva, ohraničení atd.).
    * Také se zde počítá jakým směrem je ulice nakloněna a podle toho se počítá naklonění názvu ulice.
    */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    /// Ohraničení vykreslování funkce
    virtual QRectF boundingRect() const override;

private:
    /**
    * @brief Funkce, která řídí pohyb vozidla po vozovce
    * @param animation Animace daného vizidla
    * @param active_anim Určuje jestli se vozidlo má nebo nemá hýbat
    * @param anim_move Určuje relativní pozici vozidla na ulici v rozmezí 0.0 - 1.0
    * @param veh Volitelný argument celého vozidla pro jeho samostatné vykreslování
    * @details Je voláno externě po zavolání fuknce @link dec_traffic_on_road @endlink a následně určí a případně omezí svoji úroveň dopravy (min 0),
    *  Následně podle dané úrovně dopravy sníží odstín červené jakožto grafickou vizualizaci zpoždění na dané cestě.
    *
    */
    void test_anim(QVariantAnimation *animation, bool *active_anim, qreal *anim_move, vehicle* veh = nullptr);
    bool anim_set{false}; ///< Proměnná, která zjišťuje jestli byla už nastavena dálka animace či nikoli

signals:
    /**
    * @brief Signál o kliknutí na ulici
    * @param self Ukazatel na sebe
    */
    void line_selected(custom_line *self);

};

#endif // CUSTOM_LINE_H
