/*******************************************************************************************
 *
 *   COMPILATION (Windows - MinGW):
 *       gcc -o main.exe main.c -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -std=c99
 *
 *   COMPILATION (Linux - GCC):
 *       gcc -o main.exe main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 *
 ********************************************************************************************/

#include "raylib.h"
#include "includes/res.h"

typedef enum
{
    SCREEN_TITLE = 0,
    SCREEN_GAMEPLAY,
    SCREEN_ENDING
} GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 600;
    int screenHeight = 300;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Dysphoria - v0.1");

    InitAudioDevice();

    // Player
    Rectangle player = {10, screenHeight / 2 - 50, 25, 100};
    float playerSpeed = 8.0f;

    // Resources loading

    Music ambient = LoadMusicStream("/resources/lake.mp3");
    PlayMusicStream(ambient);

    // General variables
    bool pause = false;
    bool finishGame = false;
    int framesCounter = 0;
    GameScreen currentScreen = SCREEN_TITLE;

    Image playerImage = LoadImage(res("character1.png"));
    Texture playerTexture = LoadTextureFromImage(playerImage);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !finishGame) // Detect window close button or ESC key
    {
        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();

        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(ambient);

        switch (currentScreen)
        {
        case SCREEN_TITLE:
        {
            framesCounter++;

            // Update TITLE screen
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = 1;
            }
        }
        break;
        case SCREEN_GAMEPLAY:
        {
            // Update GAMEPLAY screen
            if (!pause)
            {
                // Player movement logic
                if (IsKeyDown(KEY_UP))
                    player.y -= playerSpeed;
                else if (IsKeyDown(KEY_DOWN))
                    player.y += playerSpeed;
                else if (IsKeyDown(KEY_RIGHT))
                    player.x += playerSpeed;
                else if (IsKeyDown(KEY_LEFT))
                    player.x -= playerSpeed;

                if (player.y <= 0)
                    player.y = 0;
                else if ((player.y + player.height) >= screenHeight)
                    player.y = screenHeight - player.height;
            }

            if (IsKeyPressed(KEY_P))
                pause = !pause;

            if (IsKeyPressed(KEY_ENTER))
                currentScreen = 2;
        }
        break;
        case SCREEN_ENDING:
        {
            // Update ENDING screen
            if (IsKeyPressed(KEY_ENTER))
            {
                // currentScreen = 1;
                finishGame = true;
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

        switch (currentScreen)
        {
        case SCREEN_TITLE:
        {
            DrawText("DYSPHORIA", screenWidth / 1.5, screenHeight / 1.5, 30, BLACK);
            DrawText(TextFormat("Resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, BLACK);
        }
        break;
        case SCREEN_GAMEPLAY:
        {
            DrawTexture(playerTexture, player.x, player.y, WHITE);

            // Draw
            DrawText(TextFormat("Elapsed Time: %02.02f ms", GetFrameTime() * 1000), 200, 220, 20, WHITE);

            if (pause)
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

    UnloadMusicStream(ambient);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}