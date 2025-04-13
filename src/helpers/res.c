#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *res(const char *fileName)
{
    const char *prefix = "../resources/";
    char *result = malloc(strlen(prefix) + strlen(fileName) + 1);
    strcpy(result, prefix);
    strcat(result, fileName);
    return result;
}