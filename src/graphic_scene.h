/** ICP Project 2020 transport map
 * @file graphic_scene.h
 * @brief Objekt ve kterém se vykresluje mapa
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include "custom_line.h"
#include "path.h"
#include "vehicle.h"

/// Objekt na vykreslování mapoveho podkladu a spojů
class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /// Kontruktor
    explicit graphic_scene(QObject *parent = nullptr);
    QMap<int, path*> path_dict; ///< Seznam aktivních spojů na mapě
    bool line_selecting_for_close{false}; ///< Proměnná pro uzavírky cest (nepovedlo se dodělat)

public slots:
    /**
     * @brief Vytvoření nového spoje
     * @param pos Pozice šablony v poli @link defined_path @endlink
     * @param hour Hodina vytvoření spoje
     * @param min Minuta vytvoření spoje
     * @details Funkce podle @p pos najde danou šablonu, podle které se vytvoří a nahraje do sebe veškeré potřebné informace.
     */
    void generate_new_connection(int pos,int min, int hour);
    /**
     * @brief Vytvoření nové ulice
     * @param street_id Unikátní číslo ulice v seznamech
     * @param start_p Bod ze ktereho začíná ulice
     * @param end_p Bod ve kterém končí ulice
     * @param street_name Jméno dané ulice
     */
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    /**
     * @brief Vytvoření stanici na ulici
     * @param street_id Unikátní číslo ulice, na kterém se má stanice vytvořit
     * @param position Relativní pozice stanice na ulici v rozsahu 0.0 - 1.0
     */
    void create_station(int street_id,qreal position);
    /**
     * @brief Vytvoření šablony link
     * @param route_id Unikátní číslo linky v seznamu @link defined_path @endlink
     * @param streets Seznam ulic po kterých daná linka jezdí
     * @param stations Seznam ulic na kterých má linka očekávat zastávku
     * @param color Barva linky
     * @details Funkce přidá novou @link path @endlink do seznamu @link defined_path @endlink, ze které se stane šablona pro vytvoření nových spojů stejné linky.
     * V této šabloně jsou uloženy veškeré informace o dané lince.
     */
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    /**
     * @brief Vytvoření volného textu na mapě (dodatečné popisky)
     * @param content Obsah zprávy na mapě
     * @param point Bod ze kterého text začíná
     * @param font_size Velikost písma textu
     */
    void create_text(QString content,QPointF point,int font_size);
    /**
     * @brief Změna rychlosti pohybu vozidel
     * @param val Hodnota rychlostního koeficientu
     * @details Funkce zjistí aktuální trvání animace a časovače pro každý aktivní spoj, které zastaví, zbývající interval vynásobí časem a znovu je spustí
     */
    void speed_change(int val);
    /**
     * @brief Resetuje pole spojů a tím nastaví mapu do výchozí podoby
     */
    void timer_reset();
    /**
     * @brief Spustí/zastaví všechny aktivní spoje na mapě
     */
    void toggle_timers();
    /**
     * @brief Nastaví mapu do výchozí podoby
     */
    void reset_scene();

private:
    /**
     * @brief Vloží @p value na pozici @p index do pole @p map
     * @param[in,out] map Pole ulic, do kterého se vkládá další
     * @param[in] index Pozice, na kterou se má vložit @p value
     * @param[in] value Ulice na vložení do pole
     * @return Upravený seznam
     */
    QMap<int, custom_line *> insert_into_map(QMap<int, custom_line*> *map, int index, custom_line* value);
    /**
     * @brief Odstraní hodnotu ze zadaného indexu v poli
     * @param map Mapa, ze které se má hodnota odstranit
     * @param index Pozice na ostranění
     * @return Upravený seznam
     */
    QMap<int, custom_line *> remove_from_map(QMap<int, custom_line*> *map, int index);
    /**
     * @brief Zjistí, zda se v poli vyskytuje zadaná ulice
     * @param map Mapa na zkoumání
     * @param value Ulice, která se hledá
     * @return Pozice @p value v poli
     */
    int is_in_map(QMap<int, custom_line*> map, custom_line* value);
    /**
     * @brief Resetuje kliknutí na vozidla kromě vozidla s pozicí @p pos
     * @param pos Pozice, která se nemá resetovat
     * Používá se pro vyresetování při kliknutí na nové vozidlo
     */
    void reset_click_on_vehicle(int pos);
    /**
     * @brief Vyresetuje kliknutí na ulici kromě pozice @p pos
     * @param pos Pozice která se nemá resetovat
     * Používá se pro vyresetování při kliknutí na novou ulici
     */
    void reset_line_selection(int pos);
    /**
     * @brief Zjistí jestli zadané dvě linie na sebe navazují či nikoliv
     * @param l1 Linie 1
     * @param l2 Linie 2
     * @param direction Směr kterým na sebe navazují
     * @return Booleovská hodnota odpovídající informaci zda-li na sebe linie navazují či nikoliv
     */
    bool line_subsequent(QLineF l1, QLineF l2, int *direction);
    /**
     * @brief Ladící funkce pro výpis ID ulic v daném poli
     * @param map Pole na výpis
     * @return Seznam ID ulic v poli
     */
    QStringList print_street_id(QMap<int, custom_line*> map);
    QMap<int, path*> defined_path; ///< Seznam šablon pro spoje (linka)
    QMap<int, custom_line*> st_dict; ///< Seznam všech známých ulic
    QMap<int, vehicle*> vehicle_dict; ///< Seznam aktivních vozidel
    QMap<int, custom_line *> alternate_route; ///< Seznam ulic pro objízdnou trasu (nepodařilo se dokončit)
    qreal speed{1.0}; ///< Přepočítaný rychlostní koeficient
    QColor def_road_color{Qt::darkGray}; ///< Základní barva ulice
    custom_line *selected_line; ///< Právě vybraná ulice @see custom_line

private slots:
    /**
     * @brief Zachytí signál kliknutí na ulici
     * @param road Ukazatel na kliknutou ulici
     */
    void select_line(custom_line *road);
    /**
     * @brief Zachytí signál kliknutí na vozidlo
     * @param pos Pozice kliknutého vozidla
     */
    void vehicle_clicked(int pos);

signals:
    /**
     * @brief Propagování vybraného vozidla
     * @param path Spoj s aktuálním vozidlem
     */
    void circle_clicked(path *path);
    /**
     * @brief Propagování informace o tom že není vybráno žádné vozidlo
     */
    void circle_unclicked();
    /**
     * @brief Propagování vybrané ulice
     * @param road Ukazatel na ulici
     */
    void road_clicked(custom_line *road);
    /**
     * @brief Potvrzení, že reset mapy proběhl v pořádku
     */
    void reseted();
};

#endif // GRAPHIC_SCENE_H
