#ifndef PARSEARGSINCLUDED
#define PARSEARGSINCLUDED

#include "includes.h"

/**
 * \file
 * \brief Ebben található minden, ami a paraméterek feldolgozásához kell.*/

/** \brief Az indítás paramétereit ebben a struktúrában tároljuk el.
 * \param isCcompress Megadja, hogy a folyamat tömörítés (true) vagy kitömörítés (false) lesz.
 * \param inputFileName A megadott bemeneti fájl neve. Kötelező megadni megadni. Amennyiben nincs megadva, a program hibaüzenettel leáll.
 * \param outputFileName A megadott kimeneti fájl neve. Nem kötelező megadni, amennyiben nincs megadva, az alapértelmezett érték: {inputFileName}_OUT.compressed
 * \param error Megadja, hogy sikeresen be lehetett-e olvasni minden kötelező adatot. Amennyiben hiba lépett fel, true lesz az értéke.
 * \param info Megadja, hogy a "--help" paraméterekkel futtatták-e le a programot. Ebben az esetben a program hiba nélkül leáll. */
typedef struct commands {
    /// Megadja, hogy a folyamat tömörítés (true) vagy kitömörítés (false) lesz.
    bool isCcompress;
    /// A megadott bemeneti fájl neve. Kötelező megadni megadni. Amennyiben nincs megadva, a program hibaüzenettel leáll.
    char* inputFileName;
    /// A megadott kimeneti fájl neve. Nem kötelező megadni, amennyiben nincs megadva, az alapértelmezett érték: {inputFileName}_OUT.compressed
    char* outputFileName;
    /// Megadja, hogy sikeresen be lehetett-e olvasni minden kötelező adatot. Amennyiben hiba lépett fel, true lesz az értéke.
    bool error;
    /// Megadja, hogy a "--help" paraméterekkel futtatták-e le a programot. Ebben az esetben a program hiba nélkül leáll.
    bool info;
} commands;

/** \brief Feldolgozza a programnak megadott argumentumokat.
 * \param argc Hány argumentum van
 * \param argv Az argumentumok listája */
commands parseArguments (int argc, char** argv);

#endif
