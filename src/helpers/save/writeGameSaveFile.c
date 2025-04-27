#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "states.h"

/**
 * Writes SaveFile to the game save file
 */
int writeGameSaveFile(SaveFile *inputSaveFile)
{
    FILE *gameSaveFile = fopen("/Documents/dysphoria/save.bin", "wb");

    if (gameSaveFile == NULL)
    {
        perror("Cannot open records");
        return errno + 1;
    };

    size_t elements_written = fwrite(inputSaveFile, sizeof(SaveFile), 1, gameSaveFile);

    if (elements_written != 1)
    {
        perror("Cannot write to file");
        return errno + 1;
    }

    fclose(gameSaveFile);
    return true;
};
