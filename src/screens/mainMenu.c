#include "raylib.h"
#include "states.h"
#include <stdio.h>
#include "screens.h"
#include "utils.h"

//----------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------
#define TITLE_FONT_SIZE 100
#define BUTTON_FONT_SIZE 40
#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 60
#define BUTTON_SPACING 80
#define TITLE_Y_POSITION 100
#define BUTTONS_START_Y 300

static int toScreen = -1;
static int currentButton = 0;
static const char* buttonTexts[3] = {
    "Start",
    "Options", 
    "Exit"
};

void initMainMenuScreen() {
    toScreen = -1;
    currentButton = 0;
}

void updateMainMenuScreen(ScreenState *ss,SettingsFile *sf) {
    if (toScreen != -1) return;
    // Menu navigation
    if (IsKeyPressed(KEY_DOWN)) {
        currentButton = (currentButton + 1) % 3;
    }
    else if (IsKeyPressed(KEY_UP)) {
        currentButton = (currentButton - 1 + 3) % 3;
    }
    

    // Button actions
    if (IsKeyPressed(KEY_ENTER)) {
        switch(currentButton) {
            case 0:
                initIntroScreen();
                toScreen = INTRO;
                break;
            case 1:
                initOptionsScreen(sf);
                toScreen = OPTIONS;
                break;
            case 2:
                closeWindow(sf);
                break;
        }
    }
}

void drawMainMenuScreen(WindowState *ws, ResourcesState *rs) {
    // Clear background
    DrawRectangle(0, 0, ws->screenWidth, ws->screenHeight, WHITE);
    
    // Draw title
    const char* titleText = "Dysphoria";
    Vector2 titleSize = MeasureTextEx(rs->mainFontMd, titleText, TITLE_FONT_SIZE, 2);
    Vector2 titlePos = {
        (ws->screenWidth - titleSize.x) / 2,
        TITLE_Y_POSITION
    };
    DrawTextEx(rs->mainFontMd, titleText, titlePos, TITLE_FONT_SIZE, 2, BLACK);
    
    // Draw buttons
    for (int i = 0; i < 3; i++) {
        // Calculate button position
        Rectangle buttonRect = {
            (ws->screenWidth - BUTTON_WIDTH) / 2,
            BUTTONS_START_Y + (i * BUTTON_SPACING),
            currentButton == i ? BUTTON_WIDTH - 3 : BUTTON_WIDTH,
            currentButton == i ? BUTTON_HEIGHT - 3 : BUTTON_HEIGHT
        };
        
        // Draw button background
        Color bgColor = currentButton == i ? WHITE : BLACK;
        Color borderColor = currentButton == i ? BLACK : WHITE;
        Color textColor = currentButton == i ? BLACK : WHITE;
        
        DrawRectangleRec(buttonRect, bgColor);
        DrawRectangleLinesEx(buttonRect, 3, borderColor);
        
        // Draw button text
        Vector2 textSize = MeasureTextEx(rs->mainFontSm, buttonTexts[i], BUTTON_FONT_SIZE, 2);
        Vector2 textPos = {
            buttonRect.x + (buttonRect.width - textSize.x) / 2,
            buttonRect.y + (buttonRect.height - textSize.y) / 2
        };
        
        DrawTextEx(rs->mainFontSm, buttonTexts[i], textPos, BUTTON_FONT_SIZE, 2, textColor);
    }
}

void unloadMainMenuScreen() {
    // Nothing to unload
}

int finishMainMenuScreen() {
    return toScreen;
}