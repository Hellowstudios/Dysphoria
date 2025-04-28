#include "raylib.h"
#include "states.h"
#include <stdio.h>

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static int finishScreen;
static int currentButton = 0;
static const char* buttonTexts[] = {"Start", "Options", "Exit"};

void initMainMenuScreen() {
    // init variables here  
    finishScreen = 0;
};

void updateMainMenuScreen(ScreenState *ss) {
        // Update TITLE screen
       
    if (IsKeyPressed(KEY_DOWN)) {
        currentButton++;
        if (currentButton > 2) currentButton = 0;
        return;
    }

    if (IsKeyPressed(KEY_UP)) {
        currentButton--;
        if (currentButton < 0) currentButton = 2;

        return;
    }

    if (currentButton == 0) {
        if (IsKeyPressed(KEY_ENTER))
        {
            finishScreen = 1;
        }
        
        return;
    }
    
    if (currentButton == 1) {
        if (IsKeyPressed(KEY_ENTER))
        {
            finishScreen = 1;
            ss->currentScreen = OPTIONS;
        }
        
        return;
    }
        

    if (currentButton == 2) {
        if (IsKeyPressed(KEY_ENTER))
        {
            CloseWindow();
        }
        
        return;
    }
       
};

void drawMainMenuScreen(WindowState *ws, ResourcesState *rs)
{
    DrawRectangle(0, 0, ws->screenWidth, ws->screenHeight, WHITE);

    const char* text = "Dysphoria";
    int fontSize = 80;
    int textWidth = MeasureTextEx(rs->mainFont, text, fontSize, 2).x;

    DrawTextEx(rs->mainFont, text, (Vector2){(ws->screenWidth - textWidth) / 2, 50}, fontSize, 2, BLACK);

    for (size_t i = 0; i < 3; i++)
    {
        Rectangle rec = {
            (ws->screenWidth - 200) / 2,
            150 + (i * 50),
            currentButton == i ? 197 : 200,
            currentButton == i ? 37 : 40
        };

        DrawRectangleRec(
            rec,
            currentButton == i ? WHITE : BLACK
        );

        DrawRectangleLinesEx(
            rec,
            3,
            currentButton == i ? BLACK : WHITE
        );

        // Draw the text
        int buttonFontSize = 30;
        Vector2 textSize = MeasureTextEx(rs->mainFont, buttonTexts[i], buttonFontSize, 2);
        Vector2 textPosition = {
            rec.x + (rec.width - textSize.x) / 2,  // Center horizontally
            rec.y + (rec.height - textSize.y) / 2  // Center vertically
        };

        DrawTextEx(
            rs->mainFont,
            buttonTexts[i],
            textPosition,
            buttonFontSize,
            2,
            currentButton == i ? BLACK : WHITE
        );
    }
}
void unloadMainMenuScreen()
{
}

int finishMainMenuScreen()
{
    return finishScreen;
}