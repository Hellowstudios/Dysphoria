#include "raylib.h"
#include "states.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static int finishScreen;

void initMainMenuScreen()
{
    // init variables here
    finishScreen = 0;
};

void updateMainMenuScreen()
{
    // Update TITLE screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
    }
};

void drawMainMenuScreen(WindowState *ws)
{
    DrawText("DYSPHORIA", ws->screenWidth / 1.5, ws->screenHeight / 1.5, 30, WHITE);
    DrawText(TextFormat("Resolution: %ix%i", ws->screenWidth, ws->screenHeight), 10, 10, 20, BLACK);
};

void unloadMainMenuScreen()
{
}

int finishMainMenuScreen()
{
    return finishScreen;
}