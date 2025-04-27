#ifndef GAME_SAVE_H
#define GAME_SAVE_H

extern const char gameSaveFilePath[]; // Declaration only

typedef struct
{
    unsigned day : 9;    // 0-511 range
    unsigned hour : 5;   // 0-23 range
    unsigned minute : 6; // 0-59 range
} GameSaveFileData;

#endif