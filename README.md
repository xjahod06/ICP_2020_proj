# Mapa Dopravy
## Autoři: Vojtěch Jahoda (xjahod06), Silvie Němcová (xnemco06)
Jednoduchá simulace hromadné dopravy.

## Kompilace programu
Pro úspěšnou kompilaci programu je pořeba mít nainstalované Qt alespoň ve verzi 5.5.1 s funkčním příkazem `qmake`. Po použití `make` se pomocí příkazu `qmake` vytvoří a zkompiluje program do složky build, přičemž soubor na spuštění se přesune do hlavní složky s projektem.

## Použití
Program se spustí příkazem `./ICP_2020_proj`. Po spuštění se program snaží implicitně najít složku `example/` a načíst z ní soubory s příponou `.txt`, pokud však tuto složku nenajde nebo je prázdná, tak zde nastává možnost najít složku s mapovými podklady manuálně a to kliknutím na `layouts -> find my directory` v levém horním rohu. Po úspěšném nalezení adresáře se přidají nalezené soubory z něj do záložky `layouts`, kde si uživatel m,ůže libolně přepínat mezi podklady.

## Formát souboru
Program načítá ze souboru mapový podklad, jízdní řády a mapy linek. Správné příklady vstupu jsou uvedeny ve složce `example/`.
Formát souboru umožňuje jednořádkové komentáře, které začínají znakem `#`, který ale můsí být uveden na začátku řádku. řádky souboru se načítají postupně a jednotlivé informace na řádku jsou odsebe oddělena znakem `|`. Po načtení řádku se hledají klíčová slova na začátku jako `street`,`station`,`route`,`timetable` a případně `text`. Každé z těchto slov určuje význam dalších informací a to ve formátech:

`street`    -> `street|unikátní ID ulice|počáteční souřadnice ve tvaru "x,y"|konečné souřadnice ve tvaru "x,y"|jméno ulice (nepovinné)`  
>	        -> street|0|200,-50|0,0|Božětěchova

`station`   -> `station|ID ulice na které se stanice objevuje|relativní souřadnice na ulici v rozmezí 0.0 - 1.0 (0.0 je počáteční souřadnice)`  
>            -> station|0|0.64

`route`     -> `route|unikátní ID linky|ID ulic po kterých linka jede oddělené ","|ID stanic ve kterých má linka zastavit oddělené ","|barva spoje na mapě`  
>            -> route|0|0,1,2,3,4,17,18,20,9|0,1,4,18,20,9|#75aaff 

`timetable` -> `timetable|ID linky na kterou se JŘ vztahuje|začátek platnosti JŘ ve formátu "hh:mm"|konec platnosti JŘ ve formátu "hh:mm" (-1 = nikdy neskončí)
               |interval v sekundách po kterém vyjede další spoj`  
>            -> timetable|0|00:00|-1|10


## Makefile
`make`         -> přeloží soubor do složky `build/`<br>
`make doxygen` -> vytvoří doxygen dokumentaci do složky `doc/`<br>
`make pack`    -> vytvoří .zip archiv pro všechny soubory projektu<br>
`make clean`   -> smaže všechny produkty příkazů make (`build/`,`doc/`,`.zip`)<br>
 

## Seznam souborů
1. src/ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(zdrojové soubory)
2. example/ &nbsp;&nbsp;&nbsp;(příklady soubrů pro vstup)
3. doxyfile &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(konfigurační soubor pro doxygen dokumentaci)
4. Makefile
5. README.md
6. build/ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(složka pro přeložení programu)
7. doc/ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(složka pro vygenerování dokumentace)
