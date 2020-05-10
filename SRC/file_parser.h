/** ICP Project 2020 transport map
 * @file file_parser.h
 * @brief object na extrakci dat ze souboru hlavička
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <QObject>
#include <QPointF>
#include <QList>
#include <QColor>

/// extrakce dat ze soubru
class file_parser : public QObject
{
    Q_OBJECT
public:
    /// kontruktor
    explicit file_parser(QObject *parent = nullptr,QString file_name = NULL);
    /// započne parosání vstupního soubrou
    void parse_start();

private:
    /**
    * @brief zpracování jednoho řádku
    * @param line jeden řádek souboru
    * @details Funkce prvně zkotroluje první znak jestli není "#", to by znamenalo komentář a následní zahození řádku, pokud řádek začíná něčím jiným,
    *  tak řádek rozdělí podle "|" a zkontroluje první slovo (identifikátor) a podle něj zavolá další funkci.
    */
    void process_line(QString line);
    /**
    * @brief zpracování seznamu jako ulice a vyslání signálu @link create_street @endlink
    * @param list seznam rozdělených prvů z řádku
    */
    void process_street(QStringList list);
    /**
    * @brief zpracování seznamu jako stanice a vyslání signálu @link create_station @endlink
    * @param list seznam rozdělených prvů z řádku
    */
    void process_station(QStringList list);
    /**
    * @brief zpracování seznamu jako linka a vyslání signálu @link create_route @endlink
    * @param list seznam rozdělených prvů z řádku
    */
    void process_route(QStringList list);
    /**
    * @brief zpracování seznamu jako jízdní řád a vyslání signálu @link create_timetable @endlink
    * @param list seznam rozdělených prvů z řádku
    */
    void process_timetable(QStringList list);
    /**
    * @brief zpracování seznamu jako text a vyslání signálu @link create_label_text @endlink
    * @param list seznam rozdělených prvů z řádku
    */
    void process_text(QStringList list);
    /**
    * @brief vytvoření seznamu čísel z řetězce
    * @param list seznam řetězců čísel
    * @return seznam čísel v objektu QList
    */
    QList<int> get_list_from_string(QStringList list);
    /**
    * @brief vytvoření bodu typu QPointF z řetězce
    * @param point bod jako řetězev
    * @return bod typu QPointF
    */
    QPointF get_point_from_string(QString point);
    /**
    * @brief rozdělení řetězce na hodiny a minuty
    * @param[out] hour výstup extrahovanych hodin
    * @param[out] min výstup extrahovanych minut
    * @param[in] string řetězec času na extrakci
    */
    void split_hour_and_minute_from_string(int *hour, int *min, QString string);
    QString m_file_name; ///< jmeno souboru určeno při inicializaci

signals:
    /**
    * @brief vyslání signálu na vytvoření ulice
    * @param street_id unikátní číslo ulice v seznamu
    * @param start_p bod v prostoru, ve kterem začíná ulice
    * @param end_p bod v prostoru, ve kterem končí ulice
    * @param street_name název ulice
    */
    void create_street(int street_id,QPointF start_p,QPointF end_p,QString street_name);
    /**
    * @brief vyslání signálu na vytvoření stanice na ulici
    * @param street_id unikátní číslo ulice v seznamu, na kterém bude zastávka
    * @param position relativní souřadnice zastávky na ulici v rozmezí 0.0-1.0
    */
    void create_station(int street_id,qreal position);
    /**
    * @brief vyslání signálu na vytvoření linky
    * @param route_id unikátní číslo linky v seznamu
    * @param streets seznam ID ulic, po kterých povede daná linka
    * @param stations seznam ID ulic, na kterých se očekává zastávka
    * @param color barva linky dané cesty
    */
    void create_route(int route_id,QList<int> streets,QList<int> stations,QColor color);
    /**
    * @brief vyslání signálu na vytvoření jízdního řádu
    * @param route_id unikátní číslo linky
    * @param start_hour hodina ve kterou začne spoj být aktivní
    * @param start_min minuta ve kterou začne spoj být aktivní
    * @param end_hour hodina ve kterou může spoj naposledy vyjet
    * @param end_min minuta ve kterou může spoj naposledy vyjet
    * @param interval časový interval v sekundách podle kterého se vypouští další spoje
    */
    void create_timetable(int route_id,int start_hour,int start_min,int end_hour,int end_min,int interval);
    /**
    * @brief vyslání signálu na vytvoření textu
    * @param content obsah textové zprávy
    * @param point bod ve kterém se začíná textová zpráva vykreslovat
    * @param font_size velikost písma
    */
    void create_label_text(QString content,QPointF point,int font_size);
};

#endif // FILE_PARSER_H
