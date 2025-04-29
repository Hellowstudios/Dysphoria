#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "states.h"
#include "cJSON.h"
#include "utils.h"

int writeSettingsFile(SettingsFile *newSettingsFile ) {
    // open the JSON file
    char* filePath = getSettingsFilePath();
    FILE *fp = fopen(filePath, "r"); 
    if (fp == NULL) { 
        printf("Error: writeSettingsFile unable to open settings file.\n"); 
        return 1; 
    }
  
    // read the file contents into a string 
    char buffer[1024]; 
    fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    // parse the JSON data 
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 
  
    cJSON_ReplaceItemInObjectCaseSensitive(json, "fileVersion", cJSON_CreateNumber(newSettingsFile->fileVersion)); 
    cJSON_ReplaceItemInObjectCaseSensitive(json, "musicVolume", cJSON_CreateNumber(newSettingsFile->musicVolume)); 
    cJSON_ReplaceItemInObjectCaseSensitive(json, "soundVolume", cJSON_CreateNumber(newSettingsFile->soundVolume)); 
    cJSON_ReplaceItemInObjectCaseSensitive(json, "language", cJSON_CreateNumber(newSettingsFile->language)); 
    cJSON_ReplaceItemInObjectCaseSensitive(json, "fps", cJSON_CreateNumber(newSettingsFile->fps)); 

    // convert the cJSON object to a JSON string 
    char *json_str = cJSON_Print(json); 
  
    // write the JSON string to the file 
    fp = fopen(filePath, "w"); 
    if (fp == NULL) { 
        printf("Error: writeSettingsFile unable to open the file.\n"); 
        return 1; 
    } 
    printf("%s\n", json_str); 
    fputs(json_str, fp); 
    fclose(fp); 
  
    // free the JSON string and cJSON object 
    cJSON_free(json_str); 
    cJSON_Delete(json); 
  
    return 0; 
} 
