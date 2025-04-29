#include "raylib.h"
#include "screens.h"
#include "states.h"
#include "player.h"
#include "camerasystem.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
// Defines the next screen to go to
static int toScreen = -1;

void initIntroScreen(ResourcesState *rs)
{
    // init variables here
    Image playerImage1 = LoadImage("resources/img/character/walk1.png");
    Image playerImage2 = LoadImage("resources/img/character/walk2.png");
    Image roomImage = LoadImage("resources/img/objects/wood-planks.png");
    rs->playerWalk1Texture = LoadTextureFromImage(playerImage1);
    rs->playerWalk2Texture = LoadTextureFromImage(playerImage2);
    rs->room = LoadTextureFromImage(roomImage);
    UnloadImage(playerImage1);
    UnloadImage(playerImage2);
    UnloadImage(roomImage);
};
void updateIntroScreen(Camera2D *camera, MainState *ms, PlayerMovementState *pms)
{
    // Update GAMEPLAY screen
    UpdatePlayerMovement(ms, pms);
    UpdateGameCamera(camera,pms);

    if (IsKeyPressed(KEY_ENTER)) {
        initEndingScreen();
        toScreen = ENDING;
    }
};


void drawIntroScreen(ResourcesState *rs, MainState *ms, PlayerMovementState *pms)
{
    DrawTexture(rs->room, 0, 0, WHITE);
    DrawTexture(rs->playerWalk1Texture, pms->player.x, pms->player.y, WHITE);
    if (ms->pause)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.8f));
        DrawText("GAME PAUSED", 320, 200, 30, RED);
    }
};

void unloadIntroScreen(ResourcesState *rs)
{
    UnloadTexture(rs->playerWalk1Texture);
    UnloadTexture(rs->playerWalk2Texture);
};

int finishIntroScreen()
{
    return toScreen;
};
