#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "states.h"

/**
 * Reads the game save file and returns the SaveFile
 */
int readGameSaveFile()
{
    FILE *records = fopen("/Documents/dysphoria/save.bin", "rb");

    if (records == NULL)
    {
        perror("Cannot open records");
        return errno + 1;
    }

    struct SaveFile *obuff = malloc(sizeof(SaveFile));

    // Reads the entire struct at once
    size_t elements_read = fread(obuff, sizeof(SaveFile), 1, records);

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
