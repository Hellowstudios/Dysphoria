#include "raylib.h"
#include "resourceManager.h"
#include "gameStateManager.h"
#include "inputManager.h"
#include "screens.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void DrawGame(GameStateManager *gm, ResourceManager *rm, Rectangle *player);

int main(void)
{
    // Initialization
    //--------------    ------------------------------------------------------------------------
    int screenWidth = 600;
    int screenHeight = 300;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Dysphoria - v0.1");
    InitAudioDevice();
    // Resources loading
    ResourceManager rm;
    InitResources(&rm);

    // Game manager
    GameStateManager gm = ConstructGameStateManager();
  
    // Player
    Rectangle player = {10, screenHeight / 2 - 50, 25, 100};
    float playerSpeed = 8.0f;

    PlayMusicStream(rm.ambient);

    // General variables
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !gm.finishGame) // Detect window close button or ESC key
    {
        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();

        UpdateGame(&gm, &rm, &player);
        DrawGame(&gm, &rm, &player);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadResources(&rm);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void DrawGame(GameStateManager *gm, ResourceManager *rm, Rectangle *player)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    BeginDrawing();
    ClearBackground(BLACK);

    switch (gm->currentScreen)
    {
        case MAIN_MENU: drawMainMenuScreen(rm, player); break;
        case INTRO: drawIntroScreen(rm, player); break;
        case ENDING: drawEndingScreen(rm, player); break;
    }

    EndDrawing();
}

void UpdateGame(GameStateManager *gm, ResourceManager *rm, Rectangle *player)
{
    UpdateMusicStream(rm.ambient);

    switch (gm.currentScreen)
    {
        case MAIN_MENU:
        {
            updateMainMenuScreen(gm);
            
            if (finishMainMenuScreen())
            {
                initIntroScreen();
                unloadMainMenuScreen();
            }
        } break;        
        case INTRO:
        {
            updateIntroScreen(gm);

            if (finishIntroScreen())
            {
                initEndingScreen();
                unloadIntroScreen();
            }
        } break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                // currentScreen = 1;
                gm.finishGame = true;
            }
        } break;
        default:
            break;
    }
}