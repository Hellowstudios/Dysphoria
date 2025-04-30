
#ifndef GAME_MAIN_STATE_H
#define GAME_MAIN_STATE_H

#include "raylib.h"
#include <stdbool.h>

//----------------------------------------------------------------------------------
// Main game state
//----------------------------------------------------------------------------------
typedef struct
{
    bool pause;
    bool finishGame;
} MainState;

//----------------------------------------------------------------------------------
// Window state
//----------------------------------------------------------------------------------
typedef struct
{
    int screenWidth;
    int screenHeight;
} WindowState;

//----------------------------------------------------------------------------------
// Enum that represents the current screen
//----------------------------------------------------------------------------------
typedef enum
{
    MAIN_MENU = 0,
    INTRO,
    ENDING,
    OPTIONS,
} Screen;

//----------------------------------------------------------------------------------
// Screen related states
//----------------------------------------------------------------------------------
typedef struct
{
    Screen currentScreen;
    bool onTransition;
} ScreenState;

//----------------------------------------------------------------------------------
// All resources (audios, images) available to the game
//----------------------------------------------------------------------------------
typedef struct
{
    Texture playerWalk1Texture;
    Texture playerWalk2Texture;
    
    Texture playerLeftWalk1Texture;
    Texture playerLeftWalk2Texture;
    Texture playerLeftWalk3Texture;
    
    Texture playerRightWalk1Texture;
    Texture playerRightWalk2Texture;
    Texture playerRightWalk3Texture;

    Font mainFontSm;
    Font mainFontMd;
    Texture room;

} ResourcesState;

//----------------------------------------------------------------------------------
// Player movement related states
//----------------------------------------------------------------------------------
typedef struct PlayerMovementState {
    Rectangle player;
    float maxSpeed;
    float velocityX;    
    float velocityY;    
    float acceleration; 
    float friction;     
    bool notMoving;
} PlayerMovementState;
//----------------------------------------------------------------------------------
// Game save file data
//----------------------------------------------------------------------------------

typedef struct
{
    unsigned day : 9;    // 0-511 range
    unsigned hour : 5;   // 0-23 range
    unsigned minute : 6; // 0-59 range
} SaveFile;



//----------------------------------------------------------------------------------
// Game save file data
//----------------------------------------------------------------------------------
typedef struct
{   
    unsigned short fileVersion;
    unsigned short musicVolume; 
    unsigned short soundVolume; 
    unsigned short language; 
    unsigned short fps;  
} SettingsFile;



#endif