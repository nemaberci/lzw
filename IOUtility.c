#include "IOUtility.h"
#include "includes.h"

/**
 * \file
 * \brief Az IOUtility.h implementációja. */

void printInNBits (IOData* data, int number, int bits) {

    int totalBits = data->bitsStored + bits;
    uint32_t totalData = (data->dataStored << bits) | number;

    while (totalBits > 8) {

        putc((totalData >> (totalBits - 8)), data->file);
        totalBits -= 8;
        totalData = totalData & ((1 << totalBits) - 1);

    }

    data->bitsStored = totalBits;
    data->dataStored = totalData;

}

void printRemaining (IOData* data) {

    while (data->bitsStored > 0) {

        putc(data->dataStored << (8 - data->bitsStored), data->file);
        data->bitsStored -= 8;
        data->dataStored = data->dataStored & ((1 << data->bitsStored) - 1);

    }
    data->bitsStored = 0;
    data->dataStored = 0;

}

uint16_t readNBits (IOData* data, int bits) {

    int totalBits = data->bitsStored;
    int totalData = data->dataStored;

    while (totalBits < bits) {

        int input = getc(data->file);
        totalData = (totalData << 8) | input;
        totalBits += 8;

    }

    uint16_t toReturn = totalData >> (totalBits - bits);
    totalBits -= bits;
    totalData = totalData & ((1 << totalBits) - 1);
    data->dataStored = totalData;
    data->bitsStored = totalBits;
    return toReturn;

}

void testReadWrite (void) {

    srand(time(NULL));

    FILE* myFile;
    myFile = fopen("test.txt", "wb");

    int bits [15] = {0};
    int numbers [15] = {0};
    IOData myIOData;
    myIOData.bitsStored = 0;
    myIOData.dataStored = 0;
    myIOData.file = myFile;

    for (int i = 0; i < 15; i++) {

        bits[i] = 8 + rand() % 4;
        numbers[i] = rand() % 256;

        printf("%d is stored on %d bits\n", numbers[i], bits[i]);
        printInNBits(&myIOData, numbers[i], bits[i]);

    }

    printRemaining(&myIOData);
    myFile = freopen("test.txt", "rb", myFile);

    for (int i = 0; i < 15; i++) {

        printf("Should read: %d, data read:%d\n", numbers[i], readNBits(&myIOData, bits[i]));

    }

}
