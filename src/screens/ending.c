#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
// Defines the next screen to go to
static int toScreen;

void initEndingScreen() {
    toScreen = -1;
};

void updateEndingScreen() {
    
};

void drawEndingScreen()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    // Title
    const char *title = "THE END";
    int titleFontSize = 60;
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), title, titleFontSize, 2);
    DrawText(title, 
             (screenWidth - titleSize.x) / 2,
             screenHeight/3, 
             titleFontSize, 
             GOLD);
    
    // Thank you message
    const char *thankYou = "Thank you for playing!";
    int messageFontSize = 30;
    Vector2 messageSize = MeasureTextEx(GetFontDefault(), thankYou, messageFontSize, 2);
    DrawText(thankYou,
             (screenWidth - messageSize.x) / 2,
             screenHeight/2,
             messageFontSize,
             WHITE);
    
    // Press key prompt
    const char *prompt = "Press ENTER to return to title";
    int promptFontSize = 20;
    Vector2 promptSize = MeasureTextEx(GetFontDefault(), prompt, promptFontSize, 2);
    DrawText(prompt,
             (screenWidth - promptSize.x) / 2,
             screenHeight * 3/4,
             promptFontSize,
             LIGHTGRAY);
}
void unloadEndingScreen()
{
}

int finishEndingScreen()
{
   return toScreen;
}