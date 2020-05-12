/** ICP Project 2020 transport map
 * @file mainwindow.h
 * @brief Hlavní okno programu
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "progress_bar.h"
#include "custom_line.h"
#include "graphic_scene.h"
#include "file_parser.h"
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// Hlavní okno programu
class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    /**
     * @brief Zvětšení mapy
     */
    void zoom_in();
    /**
     * @brief Zmenšení mapy
     */
    void zoom_out();
    /**
     * @brief Zmenšení/zvětšení mapy, dle pohybu na posuvníku
     * @param val Aktuální hodnota slideru
     */
    void zoom_slide(int val);
    /**
     * @brief Zastaví pohyb na mapě
     */
    void toggle_stop_button();
    /**
     * @brief Zvýší provoz na vybrané ulici
     */
    void inc_traffic_on_road();
    /**
     * @brief Sníží provoz na vybrané ulici
     */
    void dec_traffic_on_road();
    /**
     * @brief Pozůstatek po pokusu o uzavření ulice
     */
    void close_active_road();
    /**
     * @brief Načte rozložení mapy a spoje ze souboru
     * @param name Jméno souboru k načtení
     */
    void load_layout(QString name);
    /**
     * @brief Spustí prohlížeč souborů
     */
    void browse();

public:
    /// Hlavní okno programu
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    /**
     * @brief Nastaví aktivní silnice
     * @param road Ukazatel na vybranou silnici
     */
    void set_active_road(custom_line *road);

private:
    /**
     * @brief Inicializuje grafické scény
     */
    void init_scene();
    progress_bar *progress_scene; ///< Grafické scéna pro znároznění pohybu vozidla @see progress_bar
    graphic_scene *scene; ///< Grafická scéna pro znároznění pohybu na mapě @see graphic_scene
    Ui::MainWindow *ui; ///< Všechny prvky, které se ukážou na hlavní obrazovce programu
    custom_line *active_line{nullptr}; ///< Ukazatel na vybranou ulici @see custom_line
    file_parser *parser{nullptr}; ///< Ukazatel na objekt analyzující informace ze souborů @see file_parser
    QMenu *layouts; ///< Položka menu na výběr map

protected:
    /**
     * @brief Qt funkce detekující pohyb kolečka myši
     * @details Tato funkce slouží na virtuální pohyb posuvníku, který přibližuje/oddaluje mapu
     */
    virtual void wheelEvent(QWheelEvent *event) override;
    /**
     * @brief Qt funkce detekující změnu velikosti okna
     * Slouží pro roznoměrné zvetšení či zmenšení grafické scény @link progress_bar @endlink
     */
    virtual void resizeEvent(QResizeEvent* event) override;

};
#endif // MAINWINDOW_H
