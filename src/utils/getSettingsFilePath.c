#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Returns settings file path in the operating system.
//----------------------------------------------------------------------------------
char* getSettingsFilePath() {
    char *dysphoriaDir = getDysphoriaDir();

    #ifdef _WIN32
        char *filePath = malloc(strlen(dysphoriaDir) + 20);
        sprintf(filePath, "%s/settings.json", dysphoriaDir);

        return filePath;
    #elif __linux__
        char *filePath = malloc(strlen(dysphoriaDir) + 20);
        sprintf(filePath, "%s/settings.json", dysphoriaDir);
        
        return filePath;
    #endif
}
  