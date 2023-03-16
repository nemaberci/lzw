#include "includes.h"
#include "compress.h"

/**
 * \file
 * \brief A compress.h implementációja.*/

void initCompressDict (void) {

    memset(compressDictionary, 0, MAX_VALUE * (sizeof(compressData)));
    for (int i = 0; i < 256; i++) {

        compressDictionary[i].value = i;

    }

}

void compress (FILE* inputFile, FILE* outputFile) {

    initCompressDict();

    IOData outputIOData;
    /* Init outputIOData */
    outputIOData.bitsStored = 0;
    outputIOData.dataStored = 0;
    outputIOData.file = outputFile;

    int currentInput = getc(inputFile);
    //printf("First input is: %d\n", currentInput);
    if (currentInput == EOF)
        return;
    compressData* currentElement = &compressDictionary[currentInput];
    int currentValue = 256, bitsUsed = 7;

    //printf("Compressed:   ");

    do {

        if (currentValue == MAX_VALUE) {

            initCompressDict();
            currentValue = 256;
            bitsUsed = 8;
            if (currentInput == EOF)
                return;
            currentElement = &compressDictionary[currentInput];
            //printf("\nResetting at character %c\n", currentInput);
            //printf("Current IOData: bits: %d, data: %d\n\n", outputIOData.bitsStored, outputIOData.dataStored);

        } else {

            if (currentValue > (1 << bitsUsed)) {
                bitsUsed++;
            }

        }

        currentInput = getc(inputFile);
        //printf("Current input is: %d\n", currentInput);
        if (currentInput == EOF) {

            printInNBits(&outputIOData, currentElement->value, bitsUsed);
            printRemaining(&outputIOData);
            break;

        }

        if (currentElement->next[currentInput] != 0) {

            //printf("Going down the line\n");
            currentElement = &compressDictionary[currentElement->next[currentInput]];
            continue;

        } else {

            compressDictionary[currentValue].value = currentValue;
            currentElement->next[currentInput] = currentValue;
            currentValue++;
            //printf("Adding to value %d\n", currentValue - 1);

        }

        //printf("Writing %d in %d bits\n", currentElement->value, bitsUsed);

        //printf("%d, ", currentElement->value);

        printInNBits(&outputIOData, currentElement->value, bitsUsed);

        currentElement = &compressDictionary[currentInput];

    } while (1);

    printf("\n");

}


