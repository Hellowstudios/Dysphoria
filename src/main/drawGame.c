
#include <stdio.h>
#include "raylib.h"
#include "states.h"
#include "screens.h"

void drawGame(
    ResourcesState *rs,
    MainState *ms,
    ScreenState *ss,
    WindowState *ws
) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ss->currentScreen)
    {
    case MAIN_MENU:
        EndMode2D();
        drawMainMenuScreen(ws, rs);
        break;
    case INTRO:
        drawIntroScreen(rs, ms);
        EndMode2D();  // Add this to end 2D mode before transition
        break;
    case ENDING:
        EndMode2D();
        drawEndingScreen();
        break;
    case OPTIONS:
        EndMode2D();
        drawOptionsScreen(rs);
        break;
    }

    if (ss->onTransition)
        DrawScreenTransition(ws);

    EndDrawing();
}
