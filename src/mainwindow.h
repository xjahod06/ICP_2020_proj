/**
 * @mainpage ICP-2020
 * @author Vojtěch Jahoda (xjahod06)
 * @author Silvie Němcová (xnemco06)
 */
/** ICP Project 2020 transport map
 * @file mainwindow.h
 * @brief hlavní okno programu hlavička
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

//hlavni okno programu
class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    /**
     * @brief zvětšení mapy
     */
    void zoom_in();
    /**
     * @brief zmenšení mapy
     */
    void zoom_out();
    /**
     * @brief zmenšení/zvětšení mapy, dle pohybu na slideru
     * @param val aktuální hodnota slideru
     */
    void zoom_slide(int val);
    /**
     * @brief zastaví pohyb na mapě
     */
    void toggle_stop_button();
    /**
     * @brief zvýší provoz na vybrané ulici
     */
    void inc_traffic_on_road();
    /**
     * @brief sníží provoz na vybrané ulici
     */
    void dec_traffic_on_road();
    /**
     * @brief pozustatek po pokusu o uzavření ulice
     */
    void close_active_road();
    /**
     * @brief načte rozložení mapy a spoje ze souboru
     * @param name jméno souboru k načtení
     */
    void load_layout(QString name);
    /**
     * @brief spustí prohlížeč souborů
     */
    void browse();

public:
    /// hlavní okno programu
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    /**
     * @brief nastaví aktivní silnice
     * @param road ukazatel na vybranou silnici
     */
    void set_active_road(custom_line *road);

private:
    /**
     * @brief inicializuje grafické scény
     */
    void init_scene();
    progress_bar *progress_scene; ///< grafické scéna pro znároznění pohybu vozidla @see progress_bar
    graphic_scene *scene; ///< grafická scéna na znároznění pohybu na mapě @see graphic_scene
    Ui::MainWindow *ui; ///< všechny prvky co se ukážou na hlavní obrazovce programu
    custom_line *active_line{nullptr}; ///< ukazatel na vybraou ulici @see custom_line
    file_parser *parser{nullptr}; ///< ukazatel na objekt na parsování informaci ze soubroů @see file_parser
    QMenu *layouts; ///< položka menu na výběr layoutu map

protected:
    /**
     * @brief qt funkce na detekci kolečka myši
     * @details tato fuknce slouží na virtuální pohyb zoom slideru a tím pádem na přiblížení či oddálení obrazu
     */
    virtual void wheelEvent(QWheelEvent *event) override;
    /**
     * @brief qt funkce na detekci změny velikosti okna
     * slouží pro roznoměrné zvetšení či zmenšení grafické scény @link progress_bar @endlink
     */
    virtual void resizeEvent(QResizeEvent* event) override;

};
#endif // MAINWINDOW_H
