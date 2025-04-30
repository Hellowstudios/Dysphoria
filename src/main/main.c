#include "raylib.h"
#include "screens.h"
#include "camerasystem.h"
#include <stdio.h>
#include "utils.h"
#include "helpers.h"
#include "main.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // --------------------------------------------------------------------------------------
    // Game initialization
    // --------------------------------------------------------------------------------------
    WindowState ws = {1920, 1080};

    printf("INFO: Initilizing window\n");
    InitWindow(ws.screenWidth, ws.screenHeight, "Dysphoria - v0.1");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    printf("INFO: Initilizing audio\n");
    InitAudioDevice();
    
    SettingsFile* sf = readSettingsFile();
    printf("INFO: Setting target fps\n");
    SetTargetFPS(sf->fps);

    printf("INFO: Initilizing resources\n");
    ResourcesState *rs = initilizeResources();
 
    printf("INFO: Initilizing game\n");
    printf("INFO: Reading settings file\n");
  
    MainState ms = {
        .finishGame = false,
        .pause = false,
    };
    ScreenState ss ={MAIN_MENU, false};

    SetExitKey(0);

    // We initialize the main menu screen here because this is the first screen we will draw
    initMainMenuScreen();
    
    // --------------------------------------------------------------------------------------
    // Main game loop
    // --------------------------------------------------------------------------------------
    printf("INFO: Started game main loop\n");
    while (!ms.finishGame) // Detect window close button or ESC key
    {
        ws.screenWidth = GetScreenWidth();
        ws.screenHeight = GetScreenHeight();
        
        // Update game logic
        updateGame(&ms, rs, &ss, &ws, &sf);
        // Draw game logic MainState *ms,
        drawGame(rs, &ms, &ss ,&ws);
    }

    // --------------------------------------------------------------------------------------
    // De-Initialization
    // --------------------------------------------------------------------------------------
    closeWindow(sf);

    return 0;
}
