#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cJSON.h"
#include "states.h"
#include "utils.h"

//----------------------------------------------------------------------------------
// Reads the settings file and returns a pointer to the data. If the file does not
// exist, it will create a new one with default values.
//----------------------------------------------------------------------------------
SettingsFile *readSettingsFile()
{
    char *filePath = getSettingsFilePath();

    //----------------------------------------------------------------------------------
    // Try to read and return the settings file
    //----------------------------------------------------------------------------------
    FILE *readFile = fopen(filePath, "a+");  // Changed from "r+" to "a+"
    SettingsFile *data = malloc(sizeof(SettingsFile));

    if (readFile == NULL) {
        perror("Cannot open settings file");
        exit(errno + 1);
    };

    char buffer[1024] = {0};
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, readFile);
    fclose(readFile);

    if (bytesRead > 0) {
        cJSON *json = cJSON_Parse(buffer);
        if (json) {
            // Parse existing settings
            cJSON *item;
            item = cJSON_GetObjectItem(json, "fileVersion");
            data->fileVersion = item ? cJSON_GetNumberValue(item) : 1;

            item = cJSON_GetObjectItem(json, "musicVolume"); 
            data->musicVolume = item ? cJSON_GetNumberValue(item) : 50;

            item = cJSON_GetObjectItem(json, "soundVolume");
            data->soundVolume = item ? cJSON_GetNumberValue(item) : 50;

            item = cJSON_GetObjectItem(json, "language");
            data->language = item ? cJSON_GetNumberValue(item) : 0;

            item = cJSON_GetObjectItem(json, "fps");
            data->fps = item ? cJSON_GetNumberValue(item) : 60;
            
            cJSON_free(json);

            printf("INFO: Successfully read settings file\n");
            printf("INFO: fileVersion: %i\n", data->fileVersion);
            printf("INFO: musicVolume: %i\n", data->musicVolume);
            printf("INFO: soundVolume: %i\n", data->soundVolume);
            printf("INFO: language: %i\n", data->language);
            printf("INFO: fps: %i\n", data->fps);

            return data;
        }
    }

    printf("INFO: Settings file not found, creating new one\n");
    //----------------------------------------------------------------------------------
    //  If the file is empty, create a new one with default values
    //----------------------------------------------------------------------------------
    FILE *writeFile = fopen(filePath, "w");  // Use filePath here instead of empty string
    cJSON *newJson = cJSON_CreateObject(); 
    // Set default values
    data->fileVersion = 1;
    data->musicVolume = 50;
    data->soundVolume = 50;
    data->language = 0;
    data->fps = 60;

    // Write defaults to JSON
    cJSON_AddNumberToObject(newJson, "fileVersion", data->fileVersion);
    cJSON_AddNumberToObject(newJson, "musicVolume", data->musicVolume);
    cJSON_AddNumberToObject(newJson, "soundVolume", data->soundVolume);
    cJSON_AddNumberToObject(newJson, "language", data->language);
    cJSON_AddNumberToObject(newJson, "fps", data->fps);

    // convert the cnewJson object to a newJson string 
    char *newJson_str = cJSON_Print(newJson); 

    int elementsWritten = fputs(newJson_str, writeFile); 

    // free the newJson string and cnewJson object
    cJSON_free(newJson); 
    
    printf("elementsWritten: %d\n", elementsWritten);
    
    // if write succeeded
    fclose(writeFile);
    return data;
}
