#include "gameStateManager.h"

void initIntroScreen(GameStateManager *gm) {

};

void updateIntroScreen(GameStateManager *gm) {

};

void drawIntroScreen(GameStateManager *gm)
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

void unloadIntroScreen(GameStateManager *gm)
{
}

void finishIntroScreen(GameStateManager *gm)
{
}