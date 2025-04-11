/*******************************************************************************************
 *
 *   raylib pong
 *
 *   COMPILATION (Windows - MinGW):
 *       gcc -o $(NAME_PART).exe $(FILE_NAME) -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -std=c99
 *
 *   COMPILATION (Linux - GCC):
 *       gcc -o $(NAME_PART).exe $(FILE_NAME) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 ********************************************************************************************/

#include "raylib.h"

typedef enum
{
    SCREEN_TITLE,
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
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "Dysphoria");

    InitAudioDevice();

    // Player
    Rectangle player = {10, screenHeight / 2 - 50, 25, 100};
    float playerSpeed = 8.0f;
    int playerScore = 0;

    // Resources loading

    Music ambient = LoadMusicStream("resources/lake.mp3");
    PlayMusicStream(ambient);

    // General variables
    bool pause = false;
    bool finishGame = false;
    int framesCounter = 0;
    GameScreen currentScreen = SCREEN_TITLE;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !finishGame) // Detect window close button or ESC key
    {
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
                currentScreen = 2;
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
                currentScreen = 3;
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

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case SCREEN_TITLE:
        {
            // Draw TITLE screen
            // DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            // DrawText("SCREEN TITLE", 10, 10, 30, DARKGREEN);

            if ((framesCounter / 30) % 2)
                DrawText("PRESS ENTER to START", 200, 300, 30, BLACK);
        }
        break;
        case SCREEN_GAMEPLAY:
        {

            ImageDrawRectangle("./resources/character1.png", player.x, player.y, player.width, player.height, BLUE);

            // Draw hud
            DrawText(TextFormat("%04i", playerScore), 100, 10, 30, BLUE);

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
    UnloadTexture(texLogo);
    UnloadFont(fntTitle);

    UnloadMusicStream(ambient);

    CloseAudioDevice();

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}