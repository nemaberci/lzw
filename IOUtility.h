#ifndef IOUTILITYINCLUDED
#define IOUTILITYINCLUDED
#include "includes.h"

/**
 * \file
 * \brief Ebben a fájlban található minden, ami N bit adat ki-, es beolvasásához kell.
 */

/** A szótárban maximum ennyi bit hosszan tárolunk adatot. Alapértelmezetten 12. */
#define MAX_BITS 12
/** A szótárakban maximum 2^MAX_BITS adatot tudunk tarolni, a MAX_VALUE értékét erre állítjuk be. */
#define MAX_VALUE (1 << MAX_BITS)

/** \brief A struktúra, amellyel ki-, es be tudunk olvasni N bit adatot. A struktúrában elmentjük a be / kimeneti fájlt es a tárolt adatot.
 * \param file A be vagy kimeneti fájl.
 * \param dataStored Az eltárolt adat. dataStored mindig kisebb, mint 2^bitsStored.
 * \param bitsStored Megadja, hány biten tároljuk a dataStored adatot. */
typedef struct InputOutputData {
    /// A be vagy kimeneti fájl.
    FILE* file;
    /// Az eltárolt adat. dataStored mindig kisebb, mint 2^bitsStored.
    int bitsStored;
    /// Megadja, hány biten tároljuk a dataStored adatot.
    int dataStored;
} IOData;

/** \brief Kiir egy N bites számot, beleszámítva az eddig kiírtakat.
 * \param data Ebben tároljuk az elozo kiírás / eddigi kiírások adatait.
 * \param number A kiírandó szám
 * \param bits A kiírandó szám hány biten van megadva. */
void printInNBits (IOData* data, int number, int bits);

/** \brief Kiírja az elrátolt adatokat, 0-val feltöltve jobb oldalról. */
void printRemaining (IOData* data);

/** \brief Beolvas egy N bites számot, beleszámítva az eddig beolvasottakat.
 * \param data Ebben tároljuk az eddig beolvasottakat.
 * \param bits Megadja a beolvasott adat hány biten szerepel. */
uint16_t readNBits (IOData* data, int bits);

/** \brief Tesztfüggvény, amely véletlenszerű szamokat ír es olvas be véletlenszerű biten biten.
 * Eltárolunk véletlenszerűen generált számokat és véletlenszerűen generált bitszámot (8 és 12 között).
 * Kiírjuk a számokat a hozzájuk rendelt bitszámon, majd beolvassuk őket ugyanennyi bitről. A végén összehasonlítjuk
 * a kettő adatot. */
void testReadWrite (void);

#endif // IOUTILITYINCLUDED
