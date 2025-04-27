#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static int finishScreen;

void initEndingScreen()
{
    // init variables here
    finishScreen = 0;
};

void updateEndingScreen()
{
    // Update ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
    }
};

void drawEndingScreen()
{
    DrawText("ENDING", 320, 200, 30, RED);
};

void unloadEndingScreen()
{
}

int finishEndingScreen()
{
    return finishScreen;
}