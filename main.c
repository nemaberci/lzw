#include "includes.h"
#include "compress.h"
#include "decompress.h"
#include "parseArgs.h"

/**
 * \file
 * \brief Paraméterek feldolgozása, fájl tömörítése / kitömörítése. */

int main(int argc, char** argv)
{
/*
    char inputFileName[] = "random_short.txt";
    char outputFileName[] = "output_random_short.txt";

    printf("Opening files\n");
    FILE* inputFile = fopen(inputFileName, "rb");
    FILE* outputFile = fopen(outputFileName, "wb");
    compress(inputFile, outputFile);
    printf("Compression over\n");
    fclose(outputFile);



    outputFile = fopen(outputFileName, "rb");
    FILE* decompressedFile = fopen("decompressed_random_short.txt", "wb");
    printf("Starting decompression\n");
    decompress(outputFile, decompressedFile);

    printf("Decompression over\n");
    fclose(decompressedFile);

    printf("Finished\n");
*/
    commands Commands = parseArguments(argc, argv);

    if (Commands.info) {

        return 0;

    }

    if (Commands.error) {
        printf("Error has occured\n");
        return 1;
    }

    printf("%s file %s into %s\n", Commands.isCcompress ? "compressing" : "decompressing", Commands.inputFileName, Commands.outputFileName);

    FILE* inputFile = fopen(Commands.inputFileName, "rb");
    FILE* outputFile = fopen(Commands.outputFileName, "wb");

    if (Commands.isCcompress) {

        compress(inputFile, outputFile);

    } else {

        decompress(inputFile, outputFile);

    }

    return 0;
}
