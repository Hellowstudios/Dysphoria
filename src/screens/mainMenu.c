#include "gameStateManager.h"

void initMainMenuScreen(GameStateManager *gm) {

};

void updateMainMenuScreen(GameStateManager *gm) {
        // Update TITLE screen
        if (IsKeyPressed(KEY_ENTER))
        {
            gm.currentScreen = 1;
        }
};

void drawMainMenuScreen(GameStateManager *gm)
{
    DrawText("DYSPHORIA", screenWidth / 1.5, screenHeight / 1.5, 30, WHITE);
    DrawText(TextFormat("Resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, BLACK);
};

void unloadMainMenuScreen(GameStateManager *gm)
{
}

void finishMainMenuScreen(GameStateManager *gm)
{
}