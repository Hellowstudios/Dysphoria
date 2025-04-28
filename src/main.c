#include "raylib.h"
#include "screens.h"
#include "cameraSystem.h"

void DrawGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms,
    Camera2D camera)
{
    // int screenHeight = GetScreenHeight();
    // int screenWidth = GetScreenWidth();
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ss->currentScreen)
    {
    case MAIN_MENU:
        EndMode2D();
        drawMainMenuScreen(ws);
        break;
    case INTRO:
        BeginMode2D(camera);
        drawIntroScreen(rs, ms, pms);
        break;
    case ENDING:
        EndMode2D();
        drawEndingScreen();
        break;
    }

    if (ss->onTransition)
        DrawScreenTransition();

    EndDrawing();
}

void UpdateGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms,
    Camera2D *camera)
{
    if (!ss->onTransition)
    {
        switch (ss->currentScreen)
        {
        case MAIN_MENU:
        {
            updateMainMenuScreen();

            if (finishMainMenuScreen())
            {
                initIntroScreen(rs);
                TransitionToScreen(ss, INTRO);
                unloadMainMenuScreen();
            }
        }
        break;
        case INTRO:
        {
            updateIntroScreen(camera,ms, pms);

            if (finishIntroScreen())
            {
                initEndingScreen();
                TransitionToScreen(ss, ENDING);
                unloadIntroScreen(rs);
            }
        }
        break;
        case ENDING:
        {
            updateEndingScreen();

            if (finishIntroScreen())
            {
                initEndingScreen();
                unloadIntroScreen(rs);
            }
        }
        break;
        }
    }
    else
        UpdateScreenTransition(ss);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // --------------------------------------------------------------------------------------
    // Game initialization
    // --------------------------------------------------------------------------------------
    WindowState ws = {600, 300};
    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    ResourcesState rs;

    MainState ms = {false, false};
    ScreenState ss = {MAIN_MENU, false};
    PlayerMovementState pms = {{10, ws.screenHeight / 2 - 50, 25, 100}, 8.0f};
    Camera2D camera = InitCamera(ws.screenWidth, ws.screenHeight, &pms);
    

    SetTargetFPS(60);

    // --------------------------------------------------------------------------------------
    // Main game loop
    // --------------------------------------------------------------------------------------

    while (!WindowShouldClose() && !ms.finishGame) // Detect window close button or ESC key
    {
        // Update game logic
        UpdateGame(&ms, &rs, &ss, &ws, &pms, &camera);
        // Draw game logic
        DrawGame(&ms, &rs, &ss, &ws, &pms,camera);
    }

    // --------------------------------------------------------------------------------------
    // De-Initialization
    // --------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
