#include "includes.h"
#include "decompress.h"

/**
 * \file
 * \brief A decompress.h implementációja.*/

void initDecompressDict (void) {

    memset(decompressDict, 0, sizeof(decompressData) * MAX_VALUE);

    for (int i = 0; i < 256; i++) {

        decompressDict[i].word = (char*)malloc(sizeof(char) * 1);
        decompressDict[i].word[0] = (char)i;
        //decompressDict[i].word[1] = '\0';
        decompressDict[i].length = 1;

    }
/*
    for (int i = 256; i < MAX_VALUE; i++) {

        decompressDict[i].word = (char*)malloc(sizeof(char) * 1);
        decompressDict[i].length = 0;
        decompressDict[i].word[0] = '\0';

    }
*/
}

void freeDecompressDict (void) {

    for (int i = 0; i < MAX_VALUE; i++) {

        free(decompressDict[i].word);

    }

}

void appendToDecompressDict (int lastIndex, int sourceIndex, char lastChar) {

    decompressDict[lastIndex].length = decompressDict[sourceIndex].length + 1;
    decompressDict[lastIndex].word = malloc(sizeof(char) * (decompressDict[lastIndex].length));
    decompressDict[lastIndex].word = memcpy(decompressDict[lastIndex].word, decompressDict[sourceIndex].word, decompressDict[sourceIndex].length);
    decompressDict[lastIndex].word[decompressDict[sourceIndex].length] = lastChar;

}

void decompress (FILE* inputFile, FILE* outputFile) {

    initDecompressDict();

    IOData inputIOData;
    inputIOData.bitsStored = 0;
    inputIOData.dataStored = 0;
    inputIOData.file = inputFile;

    /* First character is always 8 bit long */

    uint16_t previousInput = readNBits(&inputIOData, 8), currentInput;

    //printf("First input is: %d\n", previousInput);

    if (previousInput == EOF)
        return;

    int bitsUsed = 9;
    int currentValue = 256;
    putc(previousInput, outputFile);

    //printf("Decompressed: %d, ", previousInput);

    do {

        if (currentValue >= (1 << bitsUsed))
            bitsUsed++;

        //printf("Gonna read from %d bits\n", bitsUsed);

        currentInput = readNBits(&inputIOData, bitsUsed);
        //printf("%d, ", currentInput);

        //printf("currentInput: %d, currentValue: %d, ", currentInput, currentValue);

        if (currentInput == (uint16_t)EOF)
            break;

        if (currentInput < currentValue) {

            appendToDecompressDict(currentValue++, previousInput, decompressDict[currentInput].word[0]);

            //printf("Appending %s to the dict\n", decompressDict[currentValue - 1].word);

        } else {

            if (currentInput == currentValue) {

                appendToDecompressDict(currentValue++, previousInput, decompressDict[previousInput].word[0]);

            } else {

                printf("Error during decompression, the input file is incorrect\n");
                freeDecompressDict();
                break;

            }

            //printf("appending %s to the dict\n", decompressDict[currentValue - 1].word);

        }

        //printf("Printing %d to the file\n", currentInput);

        //printf("Printing %s\n", decompressDict[currentInput].word);
        /*if (decompressDict[currentInput].word[0] == '\0') {
            putc('\0', outputFile);
        } else {
            fprintf(outputFile, "%s", decompressDict[currentInput].word);
        }*/

        fwrite(decompressDict[currentInput].word, sizeof(char), decompressDict[currentInput].length, outputFile);

        //printf("Printed %s to the file\n", decompressDict[currentInput].word);

        if (currentValue == MAX_VALUE - 1) {

            //printf("\n\n***resetting***\n");

            //printf("At reset I have remaining bits: %d, with data %d\n", inputIOData.bitsStored, inputIOData.dataStored);
            //printf("My current input is: %d, changing it to: ", currentInput);

            freeDecompressDict();
            initDecompressDict();

            currentValue = 256;
            bitsUsed = 8;

            currentInput = readNBits(&inputIOData, 8);

            //printf("%d\n\n", currentInput);
            putc(currentInput, outputFile);

        }

        previousInput = currentInput;

    } while (1);

    freeDecompressDict();
    printf("\n");

}


