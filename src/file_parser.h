/** ICP Project 2020 transport map
 * @file file_parser.h
 * @brief Objekt pro extrakci dat ze souboru
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <QObject>
#include <QPointF>
#include <QList>
#include <QColor>

/// Extrakce dat ze soubru
class file_parser : public QObject
{
    Q_OBJECT
public:
    /// Konstruktor
    explicit file_parser(QObject *parent = nullptr,QString file_name = NULL);
    /// Započne analýzu vstupního soubrou
    void parse_start();

private:
    /**
    * @brief Zpracování jednoho řádku
    * @param line Jeden řádek souboru
    * @details Funkce nejprve zkontroluje první znak jestli není "#", to by znamenalo komentář a následně zahození řádku. Pokud řádek začíná něčím jiným,
    *  tak řádek rozdělí podle "|" a zkontroluje první slovo (identifikátor) a podle něj zavolá další funkci.
    */
    void process_line(QString line);
    /**
    * @brief Zpracování seznamu jako ulice a vyslání signálu @link create_street @endlink
    * @param list Seznam rozdělených prvů z řádku
    */
    void process_street(QStringList list);
    /**
    * @brief Zpracování seznamu jako stanice a vyslání signálu @link create_station @endlink
    * @param list Seznam rozdělených prvů z řádku
    */
    void process_station(QStringList list);
    /**
    * @brief Zpracování seznamu jako linka a vyslání signálu @link create_route @endlink
    * @param list Seznam rozdělených prvů z řádku
    */
    void process_route(QStringList list);
    /**
    * @brief Zpracování seznamu jako jízdní řád a vyslání signálu @link create_timetable @endlink
    * @param list Seznam rozdělených prvů z řádku
    */
    void process_timetable(QStringList list);
    /**
    * @brief Zpracování seznamu jako text a vyslání signálu @link create_label_text @endlink
    * @param list Seznam rozdělených prvů z řádku
    */
    void process_text(QStringList list);
    /**
    * @brief Vytvoření seznamu čísel z řetězce
    * @param list Seznam řetězců čísel
    * @return Seznam čísel v objektu QList
    */
    QList<int> get_list_from_string(QStringList list);
    /**
    * @brief Vytvoření bodu typu QPointF z řetězce
    * @param point Bod jako řetězec
    * @return Bod typu QPointF
    */
    QPointF get_point_from_string(QString point);
    /**
    * @brief Rozdělení řetězce na hodiny a minuty
    * @param[out] hour Výstup extrahovanych hodin
    * @param[out] min Výstup extrahovanych minut
    * @param[in] string Řetězec času na extrakci
    */
    void split_hour_and_minute_from_string(int *hour, int *min, QString string);
    QString m_file_name; ///< Jméno souboru určeno při inicializaci

signals:
    /**
    * @brief Vyslání signálu na vytvoření ulice
    * @param street_id Unikátní číslo ulice v seznamu
    * @param start_p Bod v prostoru, ve kterem začíná ulice
    * @param end_p Bod v prostoru, ve kterem končí ulice
    * @param street_name Název ulice
    */
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    /**
    * @brief Vyslání signálu na vytvoření stanice na ulici
    * @param street_id Unikátní číslo ulice v seznamu, na kterém bude zastávka
    * @param position Relativní souřadnice zastávky na ulici v rozmezí 0.0-1.0
    */
    void create_station(int street_id,qreal position);
    /**
    * @brief Vyslání signálu na vytvoření linky
    * @param route_id Unikátní číslo linky v seznamu
    * @param streets Seznam ID ulic, po kterých povede daná linka
    * @param stations Seznam ID ulic, na kterých se očekává zastávka
    * @param color Barva linky dané cesty
    */
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    /**
    * @brief Vyslání signálu na vytvoření jízdního řádu
    * @param route_id Unikátní číslo linky
    * @param start_hour Hodina, ve kterou začne spoj být aktivní
    * @param start_min Minuta, ve kterou začne spoj být aktivní
    * @param end_hour Hodina, ve kterou může spoj naposledy vyjet
    * @param end_min Minuta, ve kterou může spoj naposledy vyjet
    * @param interval Časový interval v sekundách, podle kterého se vypouští další spoje
    */
    void create_timetable(int route_id,int start_hour,int start_min,int end_hour,int end_min,int interval);
    /**
    * @brief Vyslání signálu na vytvoření textu
    * @param content Obsah textové zprávy
    * @param point Bod ve kterém se začíná textová zpráva vykreslovat
    * @param font_size Velikost písma
    */
    void create_label_text(QString content,QPointF point,int font_size);
};

#endif // FILE_PARSER_H
