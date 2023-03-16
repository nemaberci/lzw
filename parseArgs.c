#include "includes.h"
#include "parseArgs.h"

/**
 * \file
 * \brief A parseArgs.h implementációja.*/
commands parseArguments (int argc, char** argv) {

    commands toReturn;
    toReturn.inputFileName = NULL;
    toReturn.outputFileName = NULL;
    toReturn.isCcompress = true;
    bool commandRead = false;
    toReturn.info = false;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--help") == 0) {

            toReturn.info = true;

            printf("A program futtatasa a kovetkezokeppen folyik:\n");
            printf("NHF_c.exe <parameterek>\n");
            printf("A parameterek a kovetkezok:\n");
            printf("-d, -c: Megszabjak, hogy a program milyen muveletet hajt vegre.\n-c eseten tomorit, -d eseten kitomorit.\n");
            printf("-I, -O: Megadjak a bemeneti es kimeneti fajlok neveit.\n-I <fajlnev> a bemeneti fajl, -O <fajlnev> a kimeneti fajl\nAmennyiben nincs megadva kimeneti fajl, az alapertelmezett fajlnev: <fajlnev>_OUT.compressed\n");

            return toReturn;

        }

        if (strcmp(argv[i], "-c") == 0) {

            commandRead = true;
            toReturn.isCcompress = true;
            continue;

        }

        if (strcmp(argv[i], "-d") == 0) {

            commandRead = true;
            toReturn.isCcompress = false;
            continue;

        }

        if (strcmp(argv[i], "-I") == 0) {

            //printf("Found command -I at argument number %d\n", i);

            if (argc > i) {

                toReturn.inputFileName = malloc(sizeof(char) * (1 + strlen(argv[i + 1])));
                toReturn.inputFileName = strcpy(toReturn.inputFileName, argv[i + 1]);

            } else {

                printf("Error while interpreting input file name\n");
                break;

            }

            //printf("My inputFileName is %s\n", toReturn.inputFileName);

            continue;

        }

        if (strcmp(argv[i], "-O") == 0) {

            //printf("Found command -O at argument number %d\n", i);

            if (argc > i) {

                toReturn.outputFileName = malloc(sizeof(char) * (1 + strlen(argv[i + 1])));
                toReturn.outputFileName = strcpy(toReturn.outputFileName, argv[i + 1]);

            } else {

                printf("Error while interpreting output file name\n");
                break;

            }

            //printf("My outputFileName is %s\n", toReturn.outputFileName);

            continue;

        }

    }

    if (commandRead == false) {

        printf("No command was given.\n");
        toReturn.error = true;
        return toReturn;

    }

    if (toReturn.inputFileName == NULL) {

        toReturn.error = true;

    } else {

        //printf("inputFileName exists\n");

        if (toReturn.outputFileName == NULL) {

            //printf("outputFileName doesnt't exist, generating one right now\n");

            toReturn.outputFileName = malloc(sizeof(char) * (strlen(toReturn.inputFileName) + strlen("_OUT.compressed") + 1));
            toReturn.outputFileName = strcpy(toReturn.outputFileName, toReturn.inputFileName);
            toReturn.outputFileName = strcat(toReturn.outputFileName, "_OUT.compressed");

        } else {

            //printf("outputFileName exists\n");

        }

        toReturn.error = false;

    }

    return toReturn;

}
