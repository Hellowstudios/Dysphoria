#include "gameStateManager.h"

void initEndingScreen(GameStateManager *gm) {

};

void updateEndingScreen(GameStateManager *gm) {

};

void drawEndingScreen(GameStateManager *gm)
{
    DrawTexture(rm->playerTexture, player->x, player->y, WHITE);

    // Draw
    DrawText(TextFormat("Elapsed Time: %02.02f ms", GetFrameTime() * 1000), 200, 220, 20, WHITE);

    if (gm->pause)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.8f));
        DrawText("GAME PAUSED", 320, 200, 30, RED);
    }
};

void unloadEndingScreen(GameStateManager *gm)
{
}

void finishEndingScreen(GameStateManager *gm)
{
}