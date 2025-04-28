#include "raylib.h"
#include "screens.h"
#include "states.h"
#include "player.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
// Defines the next screen to go to
static int toScreen = -1;

void initIntroScreen() {
};

void updateIntroScreen(MainState *ms, PlayerMovementState *pms) {
    // Update GAMEPLAY screen
    updatePlayerMovement(ms, pms);

    if (IsKeyPressed(KEY_ENTER)) {
        initEndingScreen();
        toScreen = ENDING;
    }
};

void drawIntroScreen(ResourcesState *rs, MainState *ms, PlayerMovementState *pms)
{
    DrawTexture(rs->playerWalk1Texture, pms->player.x, pms->player.y, WHITE);

    if (ms->pause)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.8f));
        DrawText("GAME PAUSED", 320, 200, 30, RED);
    }
};

void unloadIntroScreen()
{
};

int finishIntroScreen()
{
    return toScreen;
};
