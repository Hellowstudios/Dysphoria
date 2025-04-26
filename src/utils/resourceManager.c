#include "raylib.h"
#include "resourceManager.h"

void LoadResources(resourcemManager *resourceManager)
{
    resourceManager->ambient = LoadMusicStream("./resources/ocean.mp3");
    Image playerImage = LoadImage("./resources/walk1.png");
    resourceManager->playerTexture = LoadTextureFromImage(playerImage);
}