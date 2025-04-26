#include "raylib.h"

typedef struct
{
    Texture playerTexture;
    Music ambient;
} resourcemManager;
void LoadResources(resourcemManager *resourceManager);