#include "raylib.h"
#include "resourceManager.h"

void LoadResources(resourceManager *resourceManager)
{
    resourceManager->ambient = LoadMusicStream("./resources/ocean.mp3");
    Image playerImage = LoadImage("./resources/walk1.png");
    resourceManager->playerTexture = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);
}
void UnloadResources(resourceManager *resourceManager)
{
    UnloadTexture(resourceManager->playerTexture);
    UnloadMusicStream(resourceManager->ambient);
}