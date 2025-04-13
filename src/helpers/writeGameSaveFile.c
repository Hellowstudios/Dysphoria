#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gameSaveFileData.h"

/**
 * Writes gameSaveFileData to the game save file
 */
int writeGameSaveFile(gameSaveFileData *inputSaveFile)
{
    FILE *gameSaveFile = fopen("/Documents/dysphoria/save.bin", "wb");

    if (gameSaveFile == NULL)
    {
        perror("Cannot open records");
        return errno + 1;
    };

    size_t elements_written = fwrite(inputSaveFile, sizeof(gameSaveFileData), 1, gameSaveFile);

    if (elements_written != 1)
    {
        perror("Cannot write to file");
        return errno + 1;
    }

    fclose(gameSaveFile);
    return true;
};
