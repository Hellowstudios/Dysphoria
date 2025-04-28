#include "raylib.h"
#include "screens.h"
#include "cameraSystem.h"
#include <stdio.h>

void InitilizeResources(
    ResourcesState *rs
) {
   rs->playerWalk1Texture = LoadTextureFromImage(LoadImage("resources/img/character/walk1.png"));
 
   rs->mainFontSm = LoadFontEx("resources/fonts/GloriaHallelujah-Regular.ttf", 40, NULL, 0xFFFF);
   SetTextureFilter(rs->mainFontSm.texture, TEXTURE_FILTER_BILINEAR); 

   rs->mainFontMd = LoadFontEx("resources/fonts/GloriaHallelujah-Regular.ttf", 120, NULL, 0xFFFF);
   SetTextureFilter(rs->mainFontMd.texture, TEXTURE_FILTER_BILINEAR);  

} 

void DrawGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    PlayerMovementState *pms,
    Camera2D camera)
{

    BeginDrawing();
    ClearBackground(BLACK);

    switch (ss->currentScreen)
    {
    case MAIN_MENU:
        EndMode2D();
        drawMainMenuScreen(ws, rs);
        break;
    case INTRO:
        BeginMode2D(camera);
        drawIntroScreen(rs, ms, pms);
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
                updateMainMenuScreen(ss);
                
                int nextScreen = finishMainMenuScreen();
                if (nextScreen != -1)
                {
                    printf("moving on to the next chapter");
                    TransitionToScreen(ss, nextScreen);
                    unloadMainMenuScreen();
                }
            } break; 
            case OPTIONS:
            {
                updateOptionsScreen();
                
                int nextScreen = finishOptionsScreen();
                if (nextScreen != -1)
                {
                    TransitionToScreen(ss, nextScreen);
                    unloadOptionsScreen();
                }
            } break;        
            case INTRO:
            {
                updateIntroScreen(ms, pms);

                int nextScreen = finishIntroScreen();
                if (nextScreen != -1)                {
                    TransitionToScreen(ss, nextScreen);
                    unloadIntroScreen();
                }
            } break;
            case ENDING:
            {
                updateEndingScreen();

                int nextScreen = finishEndingScreen();
                if (nextScreen != -1)
                {
                    TransitionToScreen(ss, nextScreen);
                    unloadEndingScreen();
                }
            } break;
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
        .mainFontSm = (Font){0},
        .mainFontMd = (Font){0}
    };
    WindowState ws = {600, 300};
    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    ResourcesState rs;

    MainState ms = {false, false};
    ScreenState ss = {MAIN_MENU, false};
    PlayerMovementState pms = {{10, ws.screenHeight / 2 - 50, 25, 100}, 8.0f};
    Camera2D camera = InitCamera(ws.screenWidth, ws.screenHeight, &pms);
    
    printf("INFO: Setting config flags\n");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    printf("INFO: Initilizing window\n");
    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");
    
    printf("INFO: Initilizing audio\n");
    InitAudioDevice();
    
    printf("INFO: Setting target fps\n");
    SetTargetFPS(60);

    SetExitKey(0);

    printf("INFO: Initilizing resources\n");
    InitilizeResources(&rs);
    
    // --------------------------------------------------------------------------------------
    // Main game loop
    // --------------------------------------------------------------------------------------

    // We initialize the main menu screen here because this is the first screen we will draw
    initMainMenuScreen();

    printf("INFO: Started game main loop\n");
    while (!ms.finishGame) // Detect window close button or ESC key
    {
        ws.screenWidth = GetScreenWidth();
        ws.screenHeight = GetScreenHeight();
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
