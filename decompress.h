
#ifndef DECOMPRESS_INCLUDED
#define DECOMPRESS_INCLUDED
#include "includes.h"

/**
 * \file
 * \brief Ebben a fájlban található minden, ami egy binárisan kódolt fójl dekódolásához kell.*/

/** \brief A compressData-hoz képest kitömörítésnél el kell tárolni a jelenlegi elem string megfelelőjét is. Ezt dinamikusan foglaljuk, ezert a program végén fel kell szabadítani.
 * \param word Ebben tároljuk a jelenlegi elem string megfelelőjét.
 * \param length El kell tárolnunk a karakterkód hosszát. Erre abban az esetben van szükség, amennyiben a tömörítetlen adat tartalmaz 0 elemet.
 * \param next A következő elem szótar-beli helye. */
typedef struct decompressData {
    /// Ebben tároljuk a jelenlegi elem string megfelelőjét.
    char* word;
    /// El kell tárolnunk a karakterkód hosszát. Erre abban az esetben van szükség, amennyiben a tömörítetlen adat tartalmaz 0 elemet.
    int length;
    /// A következő elem szótar-beli helye.
    uint16_t next [256];
} decompressData;

/** \brief A tömörítéshez használt szótar globális, így nem kell függvények között passzolgatni.
 * \param MAX_VALUE A tömb maximum 2^MAX_BITS elemből állhat.
 * A maximális elemszám 2^n, ahol n a maximális bitek száma. */
decompressData decompressDict [MAX_VALUE];

/** \brief A kitömörítéshez használt szótár inicializáló függvénye.
 * A függvény feltölti a szótárat nullákkal es beállítja az első 256 elemet {0-255}-re. */
void initDecompressDict (void);

/** \brief A kitömörítő szótar szavait felszabadítja.
 * A tömb mérete statikus, de a benne tárolt stringek dinamikusan foglaltak, ezért a kitömörítés végén fel kell szabadítani őket.
 * A függvény végigmegy a tömb elemein es felszabadítja a lefoglalt memóriát.*/
void freeDecompressDict (void);

/** \brief Hozzáfűzi a kitömörítő szótárhoz a jelenlegi elemet.
 * \param lastIndex A szótár utolsó elemének indexe. A függvény ide fogja beszúrni az elkészített elemet.
 * \param sourceIndex A szótár azon eleme, amely string végére a karaktert kell fűzni.
 * \param lastChar A karakter, amely a decompressDict[sourceIndex].word string végére lesz fűzve.
 * A függvény dinamikusan lefoglal annyi memóriát, hogy elférjen benne a sourceIndex helyen lévő string + 1 karakter.
 * Belemásolja a lefoglalt memóriába a decompressDict[sourceIndex].word stringet (mint memória-tartomány), majd a végére odarakjuk a lastChar karaktert.
 * A decompressDict[lastIndex].length-et beállítjuk a decompressDict[sourceIndex].word hosszára + 1-re, ami tartalmazni fogja az utolsó karaktert.
 * Mivel a stringet nem stringkezelő függvényekkel dolgozzuk fel, ezert nem kell helyet foglalni a lezáró nullának. */
void appendToDecompressDict (int lastIndex, int sourceIndex, char lastChar);

/** \brief Az inputFile-bol beolvasott adatot az outputFile-ba kiírja LZW algoritmus alapján kitömörítve. A fügvény addig megy, amig tud adatot olvasni a fajlbol.
 * \param inputFile a bemeneti fájl pointere. A fájlt olvasásra megnyitva kell átadni.
 * \param outputFile a kimeneti fájl pointere. A fájlt írásra megnyitva kell átadni. */
void decompress (FILE* inputFile, FILE* outputFile);

#endif // DECOMPRESS_INCLUDED

