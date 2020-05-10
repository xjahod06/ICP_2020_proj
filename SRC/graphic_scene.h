/** ICP Project 2020 transport map
 * @file graphic_scene.h
 * @brief object ve kterém se vykresluje mapa hlavička
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

/// objekt na vykreslování mapoveho podkladu a spojů
class graphic_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /// kontruktor
    explicit graphic_scene(QObject *parent = nullptr);
    QMap<int, path*> path_dict; ///< seznam aktivních spojů na mapě
    bool line_selecting_for_close{false}; ///< proměnná pro uzavírky cest (nepovedlo se dodělat)

public slots:
    /**
     * @brief vytvoření nového spoje
     * @param pos pozice šablony v poli @link defined_path @endlink
     * @param hour hodina vytvoření spoje
     * @param min minuta vytvoření spoje
     * @details Funkce podle @p pos najde danou šablonu, podle které se vytvoří a nahraje do sebe veškeré potřebné informace.
     */
    void generate_new_connection(int pos,int min, int hour);
    /**
     * @brief vytvoření nové ulice
     * @param street_id unikátní číslo ulice v seznamech
     * @param start_p bod ze ktereho začíná ulice
     * @param end_p bod ve kterém končí ulice
     * @param street_name jméno dané ulice
     */
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    /**
     * @brief vytvoření stanici na ulici
     * @param street_id unikátní číslo ulice, na kterém se má stanice vytvořit
     * @param position relativní pozice stanice na ulici v rozsahu 0.0 - 1.0
     */
    void create_station(int street_id,qreal position);
    /**
     * @brief vytvoření šablony link
     * @param route_id unikátní číslo linky v seznamu @link defined_path @endlink
     * @param streets seznam ulic po kterých daná linka jezdí
     * @param stations seznam ulic na kterých má linka očekávat zastávku
     * @param color barva linky
     * @details Funkce přidá novou @link path @endlink do seznamu @link defined_path @endlink, ze které se stane šablona pro vytvoření nových spojů stejné linky.
     * V této šabloně jsou uloženy veškeré informace o dané lince.
     */
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    /**
     * @brief vytvoření volneho textu na mapě (dodatečné popisky)
     * @param content obsah zprávy na mapě
     * @param point bod ze kterého text začíná
     * @param font_size velikost písma textu
     */
    void create_text(QString content,QPointF point,int font_size);
    /**
     * @brief změna rychlosti pohybu vozidel
     * @param val hodnota rychlostního koeficientu
     * @details funkce zjistí aktuální trvání animace a časovače pro každý aktivní spoj, které zastaví, zbývající interval vynásobí časem a znovu je spustí (občas nefunguje prfektně)
     */
    void speed_change(int val);
    /**
     * @brief resetuje pole spojů a tím nastaví mapu do defaultní podoby
     */
    void timer_reset();
    /**
     * @brief pustí/zastaví všechny aktivní spoje na mapě
     */
    void toggle_timers();
    /**
     * @brief nastaví mapu do základní podoby
     */
    void reset_scene();

private:
    /**
     * @brief vloží @p value na pozici @p index do pole @p map
     * @param[in,out] map pole ulic do ktereho se vkládá další
     * @param[in] index pozici na kterou se má vložit @p value
     * @param[in] value ulice na vložení do pole
     * @return upravený seznam
     */
    QMap<int, custom_line *> insert_into_map(QMap<int, custom_line*> *map, int index, custom_line* value);
    /**
     * @brief odstraní hodnotu ze zadaneho indexu v poli
     * @param map mapa ze které se má hodnota odstranit
     * @param index pozice na ostranění
     * @return upravený seznam
     */
    QMap<int, custom_line *> remove_from_map(QMap<int, custom_line*> *map, int index);
    /**
     * @brief zjistí zda se v poli vyskytuje zadana ulice
     * @param map mapa na zkoumání
     * @param value ulice co se zjistuje
     * @return pozice @p value v poli
     */
    int is_in_map(QMap<int, custom_line*> map, custom_line* value);
    /**
     * @brief vyresetuje kliknutí na vozidla kromě vozidla s pozicí @p pos
     * @param pos pozice která se nemá resetovat
     * používá se pro vyresetování při kliknutí na nové vozidlo
     */
    void reset_click_on_vehicle(int pos);
    /**
     * @brief vyresetuje kliknutí na ulici kromě pozice @p pos
     * @param pos pozice která se nemá resetovat
     * používá se pro vyresetování při kliknutí na novou ulici
     */
    void reset_line_selection(int pos);
    /**
     * @brief zjistí jestli zadané dvě linie na sebe navazují či nikoliv
     * @param l1 linie 1
     * @param l2 linie 2
     * @param direction směr kterým na sebe navazují
     * @return hodnota true/flase jestli na sebe navazují či nikoliv
     */
    bool line_subsequent(QLineF l1, QLineF l2, int *direction);
    /**
     * @brief debug funkce pro výpis ID ulic v daném poli
     * @param map pole na výpis
     * @return seznam ID ulic v poli
     */
    QStringList print_street_id(QMap<int, custom_line*> map);
    QMap<int, path*> defined_path; ///< seznam šablon pro spoje (linka)
    QMap<int, custom_line*> st_dict; ///< seznam všech známých ulic
    QMap<int, vehicle*> vehicle_dict; ///< seznam aktivních vozidel
    QMap<int, custom_line *> alternate_route; ///< seznam ulic pro objizdnou trasu (nepodařilo se dokončit)
    qreal speed{1.0}; ///< přepočítaný rychlostní koeficient
    QColor def_road_color{Qt::darkGray}; ///< základní barva ulice
    custom_line *selected_line; ///< právě vybraná ulice @see custom_line

private slots:
    /**
     * @brief zachytí signál kliknutí na ulici
     * @param road ukazatel na kliknutou ulici
     */
    void select_line(custom_line *road);
    /**
     * @brief zachytí signál kliknutí na vozidlo
     * @param pos pozice kliknutého vozidla
     */
    void vehicle_clicked(int pos);

signals:
    /**
     * @brief propagování vybraného vozidla
     * @param path spoj s aktuálním vozidlem
     */
    void circle_clicked(path *path);
    /**
     * @brief propagování informace o tom že není vybráno žádné vozidlo
     */
    void circle_unclicked();
    /**
     * @brief propagování vybrané ulice
     * @param road ukazatel na ulici
     */
    void road_clicked(custom_line *road);
    /**
     * @brief potvrzení že reset mapy proběhl v pořádku
     */
    void reseted();
};

#endif // GRAPHIC_SCENE_H
