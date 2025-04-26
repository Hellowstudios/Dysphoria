#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gameSaveFileData.h"

/**
 * Reads the game save file and returns the GameSaveFileData
 */
int readGameSaveFile()
{
    FILE *records = fopen("/Documents/dysphoria/save.bin", "rb");

    if (records == NULL)
    {
        perror("Cannot open records");
        return errno + 1;
    }

    struct GameSaveFileData *obuff = malloc(sizeof(GameSaveFileData));

    // Reads the entire struct at once
    size_t elements_read = fread(obuff, sizeof(GameSaveFileData), 1, records);

    if (elements_read == 1)
    {
        free(obuff);
        fclose(records);
        return elements_read;
    }
    else
    {
        free(obuff);
        fclose(records);
        return false;
    }
}
