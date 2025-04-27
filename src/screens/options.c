#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static int finishScreen;

void initOptionsScreen() {
    // init variables here
    finishScreen = 0;
};

void updateOptionsScreen() {
  
};

void drawOptionsScreen()
{
    DrawText("Options", 320, 200, 30, RED);
};

void unloadOptionsScreen()
{
}

int finishOptionsScreen()
{
   return finishScreen;
}