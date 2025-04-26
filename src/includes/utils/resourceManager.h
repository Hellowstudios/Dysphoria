#include "raylib.h"

typedef struct
{
    Texture playerTexture;
    Music ambient;
} ResourceManager;

void InitResources(ResourceManager *ResourceManager);
void UnloadResources(ResourceManager *ResourceManager);