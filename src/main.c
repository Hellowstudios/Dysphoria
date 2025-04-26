#include "raylib.h"
#include "resourceManager.h"
#include "gameStateManager.h"
#include "inputManager.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
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
    GameStateManager gm = ConstructGameStateManager(gm);
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

        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(rm.ambient);

        switch (gm.currentScreen)
        {
        case SCREEN_TITLE:
        {
            // Update TITLE screen
            if (IsKeyPressed(KEY_ENTER))
            {
                gm.currentScreen = 1;
            }
        }
        break;
        case SCREEN_GAMEPLAY:
        {
            // Update GAMEPLAY screen
            if (!gm.pause)
            {
                MovePlayer(&player, playerSpeed);
            }
            PauseGame(&gm);
        }
        break;
        case SCREEN_ENDING:
        {
            // Update ENDING screen
            if (IsKeyPressed(KEY_ENTER))
            {
                // currentScreen = 1;
                gm.finishGame = true;
            }
        }
        break;
        default:
            break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gm.currentScreen)
        {
        case SCREEN_TITLE:
        {
            DrawText("DYSPHORIA", screenWidth / 1.5, screenHeight / 1.5, 30, WHITE);
            DrawText(TextFormat("Resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, BLACK);
        }
        break;
        case SCREEN_GAMEPLAY:
        {
            DrawTexture(rm.playerTexture, player.x, player.y, WHITE);

            // Draw
            DrawText(TextFormat("Elapsed Time: %02.02f ms", GetFrameTime() * 1000), 200, 220, 20, WHITE);

            if (gm.pause)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.8f));
                DrawText("GAME PAUSED", 320, 200, 30, RED);
            }
        }
        break;
        case SCREEN_ENDING:
        {
            // Draw ENDING screen
            DrawRectangle(0, 0, screenWidth, screenHeight, RED);
            DrawText("SCREEN ENDING", 10, 10, 30, MAROON);
        }
        break;
        default:
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadResources(&rm);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
