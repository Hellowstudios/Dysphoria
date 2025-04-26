#include "raylib.h"

typedef struct
{
    Texture playerTexture;
    Music ambient;
} resourceManager;

void LoadResources(resourceManager *resourceManager);
void UnloadResources(resourceManager *resourceManager);