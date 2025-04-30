#include <stdio.h>
#include <errno.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//----------------------------------------------------------------------------------
// Returns the dysphoria directory in the operating system. If the directory does
// not exist, it will be created.
//
// Dysphoria directory is used to store settings and save files.
//----------------------------------------------------------------------------------
char* getDysphoriaDir() {
    #ifdef _WIN32
        char *appData = getenv("APPDATA");
        if (appData == NULL) {
            perror("Cannot get APPDATA directory");
            exit(1);
        }
        
        char *dysphoriaDir = malloc(strlen(appData) + 20);
        sprintf(dysphoriaDir, "%s/dysphoria", appData);

        if (mkdir(dysphoriaDir) == -1) {
            if (errno != EEXIST) {
                perror("Cannot create dysphoria directory");
                free(dysphoriaDir);
                exit(errno + 1);
            }
        }

        return dysphoriaDir;
    #elif __linux__ 
        #include <pwd.h>
        char *homeDir = getenv("HOME");
        if (homeDir == NULL) homeDir = getpwuid(getuid())->pw_dir;

        char *dysphoriaDir = malloc(strlen(homeDir) + 30);
        sprintf(dysphoriaDir, "%s/.local/share/dysphoria", homeDir);

        if (mkdir(dysphoriaDir, 0777) == -1) {
            if (errno != EEXIST) {
                perror("Cannot create dysphoria directory");
                free(dysphoriaDir);
                exit(errno + 1);
            }
        }

        return dysphoriaDir;
    #endif
}