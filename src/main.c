#include "raylib.h"
#include "screens.h"

void DrawGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms)
{
    // int screenHeight = GetScreenHeight();
    // int screenWidth = GetScreenWidth();
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ss->currentScreen)
    {
    case MAIN_MENU:
        drawMainMenuScreen(ws);
        break;
    case INTRO:
        drawIntroScreen(rs, ms, pms);
        break;
    case ENDING:
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
    PlayerMovementState *pms)
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
                initIntroScreen();
                TransitionToScreen(ss, INTRO);
                unloadMainMenuScreen();
            }
        }
        break;
        case INTRO:
        {
            updateIntroScreen(ms, pms);

            if (finishIntroScreen())
            {
                initEndingScreen();
                TransitionToScreen(ss, ENDING);
                unloadIntroScreen();
            }
        }
        break;
        case ENDING:
        {
            updateEndingScreen();

            if (finishIntroScreen())
            {
                initEndingScreen();
                unloadIntroScreen();
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

    ResourcesState rs;
    WindowState ws = {600, 300};
    MainState ms = {false, false};
    ScreenState ss = {MAIN_MENU, false};
    PlayerMovementState pms = {{10, ws.screenHeight / 2 - 50, 25, 100}, 8.0f};

    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SetTargetFPS(60);

    // --------------------------------------------------------------------------------------
    // Main game loop
    // --------------------------------------------------------------------------------------

    while (!WindowShouldClose() && !ms.finishGame) // Detect window close button or ESC key
    {
        // Update game logic
        UpdateGame(&ms, &rs, &ss, &ws, &pms);
        // Draw game logic
        DrawGame(&ms, &rs, &ss, &ws, &pms);
    }

    // --------------------------------------------------------------------------------------
    // De-Initialization
    // --------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
