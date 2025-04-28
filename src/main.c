#include "raylib.h"
#include "screens.h"
#include <stdio.h>

void InitilizeResources(
    ResourcesState *rs
) {
   rs->playerWalk1Texture = LoadTextureFromImage(LoadImage("resources/img/character/walk1.png"));
   rs->mainFont = LoadFontEx("resources/fonts/IndieFlower.ttf", 32, 0, 250);
}

void DrawGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms
) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ss->currentScreen)
    {
        case MAIN_MENU: drawMainMenuScreen(ws, rs); break;
        case INTRO: drawIntroScreen(rs, ms, pms); break;
        case ENDING: drawEndingScreen(); break;
        case OPTIONS: drawOptionsScreen(); break;
    }

    if (ss->onTransition) DrawScreenTransition();

    EndDrawing();
}

void UpdateGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms
) {
    if (!ss->onTransition)
    {
        switch (ss->currentScreen)
        {
            case MAIN_MENU:
            {
                updateMainMenuScreen(ss);
                
                if (finishMainMenuScreen())
                {
                    initIntroScreen();
                    TransitionToScreen(ss, INTRO);
                    unloadMainMenuScreen();
                }
            } break; 
            case OPTIONS:
            {
                updateOptionsScreen();
                
                if (finishOptionsScreen())
                {
                    initIntroScreen();
                    TransitionToScreen(ss, INTRO);
                    unloadOptionsScreen();
                }
            } break;        
            case INTRO:
            {
                updateIntroScreen(ms, pms);

                if (finishIntroScreen())
                {
                    initEndingScreen();
                    TransitionToScreen(ss, ENDING);
                    unloadIntroScreen();
                }
            } break;
            case ENDING:
            {
                updateEndingScreen();

                if (finishIntroScreen())
                {
                    initEndingScreen();
                    unloadIntroScreen();
                }
            } break;
        }
    } else UpdateScreenTransition(ss);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // --------------------------------------------------------------------------------------
    // Game initialization
    // --------------------------------------------------------------------------------------
  
    printf("INFO: Initilizing game\n");
    ResourcesState rs = {
        .playerWalk1Texture = (Texture){0},
        .playerWalk2Texture = (Texture){0},
        .playerLeftWalk1Texture = (Texture){0},
        .playerLeftWalk2Texture = (Texture){0},
        .playerLeftWalk3Texture = (Texture){0},
        .playerRightWalk1Texture = (Texture){0},
        .playerRightWalk2Texture = (Texture){0},
        .playerRightWalk3Texture = (Texture){0},
        .mainFont = (Font){0}
    };
    WindowState ws = {600, 300};
    MainState ms = {false, false};
    ScreenState ss = {MAIN_MENU, false};
    PlayerMovementState pms = {{10, ws.screenHeight / 2 - 50, 25, 100}, 8.0f};

    printf("INFO: Setting config flags\n");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    printf("INFO: Initilizing window\n");
    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");
    
    printf("INFO: Initilizing audio\n");
    InitAudioDevice();
    
    printf("INFO: Setting target fps\n");
    SetTargetFPS(60);
    
    printf("INFO: Initilizing resources\n");
    InitilizeResources(&rs);
    
    // --------------------------------------------------------------------------------------
    // Main game loop
    // --------------------------------------------------------------------------------------

    // We initialize the main menu screen here because this is the first screen we will draw
    initMainMenuScreen();

    printf("INFO: Started game main loop\n");
    while (!WindowShouldClose() && !ms.finishGame) // Detect window close button or ESC key
    {
        ws.screenWidth = GetScreenWidth();
        ws.screenHeight = GetScreenHeight();
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
