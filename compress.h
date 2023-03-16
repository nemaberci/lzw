
#ifndef COMPRESS_INCLUDED
#define COMPRESS_INCLUDED
#include "includes.h"

/**
 * \file
 * \brief Ebben a fájlban található minden, ami egy bináris fájl tömörítéséhez kell. */

/**  \brief Minden elemhez rendelünk egy értéket és az ezt követő karakterek tömbbeli pozícióját
 * \param value Megadja a jelenlegi string kódjat.
 * \param next A {karakter}. eleme a {string + {karakter}} listabeli pozíciója.
 */
typedef struct compressData {
    /// Megadja a jelenlegi string kódjat.
    uint16_t value;
    /// A {karakter}. eleme a {string + {karakter}} listabeli pozíciója.
    uint16_t next[256];
} compressData;

/** \brief A tömörítéshez használt szótár globális, igy nem kell függvények között passzolgatni.
 * \param MAX_VALUE A tömb maximum 2^MAX_BITS elemből állhat.
 * A maximális elemszám 2^n, ahol n a maximális bitek száma. */
compressData compressDictionary [MAX_VALUE];

/** \brief A tömörítő szótart feltölti 0-val es beállítja az első 256 karakter értékét {0-255} -re. */
void initCompressDict (void);

/** \brief Az inputFile-bol beolvasott adatot az outputFile-ba kiírja LZW algoritmus alapján tömörítve. A függvény addig megy, amíg tud adatot olvasni a fajlbol.
 * \param inputFile a bemeneti fájl pointere. A fájlt olvasásra megnyitva kell átadni.
 * \param outputFile a kimeneti fájl pointere. A fájlt írásra megnyitva kell átadni. */
void compress (FILE* inputFile, FILE* outputFile);

#endif // COMPRESS_INCLUDED


