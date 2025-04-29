#include "raylib.h"
#include "screens.h"
#include "states.h"
#include <stddef.h>
#include <stdio.h>
#include "helpers.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
#define NOT_FOCUSED_BUTTON_COLOR  (Color){ 255, 255, 255, 255 }
#define FOCUSED_BUTTON_COLOR (Color){ 200, 200, 200, 255 }

static int toScreen;
static Rectangle languageButton;
static Rectangle fpsButton;
static const char* languages[] = { "English", "Turkish" };
static int currentLanguage = 0;
static const int fpsList[] = { 30, 60, 120 };
static int currentFps = 1;  // Default to 60 FPS (index 1)
static Vector2 mousePoint;
static int selectedButton = 0;

void initOptionsScreen(SettingsFile *sf) {
    toScreen = -1;

    switch (sf->fps)
    {
    case 30:
        currentFps = 0;
        break;
    case 60:
        currentFps = 1;
        break;
    case 120:
        currentFps = 2;
        break;
    default:
        break;
    }

    currentLanguage = sf->language;

    // Initialize button positions and sizes - centered
    languageButton = (Rectangle){ GetScreenWidth()/2 - 100, 250, 200, 50 };  // Adjusted for better spacing
    fpsButton = (Rectangle){ GetScreenWidth()/2 - 100, 320, 200, 50 };  // Adjusted for better spacing
}

void updateOptionsScreen(SettingsFile *sf) {
    if (toScreen != -1) return;
    mousePoint = GetMousePosition();
    
    // Language button logic
    if (CheckCollisionPointRec(mousePoint, languageButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedButton = 0;
        currentLanguage = (currentLanguage + 1) % 2;
    }
    
    if (IsKeyDown(KEY_UP)) {
        if (selectedButton > 0) selectedButton--;
        return; 
    }

    if (IsKeyDown(KEY_DOWN)) {
        if (selectedButton < 1) selectedButton++;
        return;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedButton == 0) {
            currentLanguage = (currentLanguage + 1) % 2;
            sf->language = currentLanguage;
            writeSettingsFile(sf);
        }
        if (selectedButton == 1) {
            currentFps = (currentFps + 1) % 3;
            SetTargetFPS(fpsList[currentFps]);
            sf->fps = fpsList[currentFps];
            writeSettingsFile(sf);
        }
    }

    // FPS button logic
    if (CheckCollisionPointRec(mousePoint, fpsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedButton = 1;
        currentFps = (currentFps + 1) % 3;
        SetTargetFPS(fpsList[currentFps]);
    }
    
    // Return to main menu if ESC is pressed
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACK)) {
        printf("ESC pressed, returning to main menu\n");
        initMainMenuScreen(); 
        toScreen = MAIN_MENU;
    }
}

void drawOptionsScreen(ResourcesState *rs) {
    int screenWidth = GetScreenWidth();
    int centerX = screenWidth/2;
    const int SPACING = 50;  // Increased spacing between label and value

    // Center "OPTIONS" title
    DrawTextEx(rs->mainFontSm, "OPTIONS", 
        (Vector2){ centerX - MeasureTextEx(rs->mainFontSm, "OPTIONS", 80, 2).x/2, 150 }, 
        80, 2, WHITE);
    
    // Center language option
    float labelWidth = MeasureTextEx(rs->mainFontSm, "Language:", 40, 2).x;
    float valueWidth = MeasureTextEx(rs->mainFontSm, languages[currentLanguage], selectedButton == 0 ? 50 : 40, 2).x;
    float totalWidth = labelWidth + SPACING + valueWidth; // Increased spacing
    
    DrawTextEx(rs->mainFontSm, "Language:", 
        (Vector2){ centerX - totalWidth/2, languageButton.y + 10 }, 
        40, 2,
        WHITE
    ); 
   
    DrawTextEx(
        rs->mainFontSm, languages[currentLanguage], 
        (Vector2){ centerX - totalWidth/2 + labelWidth + SPACING, languageButton.y + 10 }, 
        selectedButton == 0 ? 50 : 40, 
        2,
        selectedButton == 0 ? NOT_FOCUSED_BUTTON_COLOR : FOCUSED_BUTTON_COLOR
    ); 
    
    // Center FPS option
    labelWidth = MeasureTextEx(rs->mainFontSm, "FPS:", 40, 2).x;
    valueWidth = MeasureTextEx(rs->mainFontSm, TextFormat("%d", fpsList[currentFps]), selectedButton == 1 ? 50 : 40, 2).x;
    totalWidth = labelWidth + SPACING + valueWidth;

    DrawTextEx(
        rs->mainFontSm,
        "FPS:", 
        (Vector2){ centerX - totalWidth/2, fpsButton.y + 10 }, 
        40, 
        2,
        WHITE
    ); 

    DrawTextEx(
        rs->mainFontSm, TextFormat("%d", fpsList[currentFps]), 
        (Vector2){ centerX - totalWidth/2 + labelWidth + SPACING, fpsButton.y + 10 }, 
        selectedButton == 1 ? 50 : 40, 
        2,
        selectedButton == 1 ? NOT_FOCUSED_BUTTON_COLOR : FOCUSED_BUTTON_COLOR
    ); 

    // Center "Press ESC to return" text
    DrawTextEx(rs->mainFontSm, "Press ESC to return",
        (Vector2){ centerX - MeasureTextEx(rs->mainFontSm, "Press ESC to return", 40, 2).x/2, 470 },
        40, 2, GRAY); 
}

void unloadOptionsScreen() {
    // Nothing to unload
}

int finishOptionsScreen() {
    return toScreen;
}