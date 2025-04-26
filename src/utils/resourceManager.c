#include "raylib.h"
#include "resourceManager.h"

void InitResources(ResourceManager *ResourceManager)
{
    ResourceManager->ambient = LoadMusicStream("./resources/ocean.mp3");
    Image playerImage = LoadImage("./resources/walk1.png");
    ResourceManager->playerTexture = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);
}
void UnloadResources(ResourceManager *ResourceManager)
{
    UnloadTexture(ResourceManager->playerTexture);
    UnloadMusicStream(ResourceManager->ambient);
}