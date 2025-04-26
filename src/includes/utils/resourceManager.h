#include "raylib.h"

typedef struct
{
    Texture playerTexture;
    Music ambient;
} resourceManager;

void InitResources(resourceManager *resourceManager);
void UnloadResources(resourceManager *resourceManager);