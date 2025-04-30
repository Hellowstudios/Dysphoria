#ifndef SCREENS_H
#define SCREENS_H

#include "states.h"

//----------------------------------------------------------------------------------
// Main Menu Screen Functions Declaration
//----------------------------------------------------------------------------------
void initMainMenuScreen();
void updateMainMenuScreen(ScreenState *ss, SettingsFile *sf, ResourcesState *rs);
void drawMainMenuScreen(WindowState *ws, ResourcesState *rs);
void unloadMainMenuScreen(void);
int finishMainMenuScreen(void);

//----------------------------------------------------------------------------------
// Intro Screen Functions Declaration
//----------------------------------------------------------------------------------
void initIntroScreen(ResourcesState *rs);
void updateIntroScreen(Camera2D *camera, MainState *ms, PlayerMovementState *pms, WindowState *ws, ResourcesState *rs);
void drawIntroScreen(ResourcesState *rs, MainState *ms, PlayerMovementState *pms);
void unloadIntroScreen(ResourcesState *rs);
int finishIntroScreen(void);

//----------------------------------------------------------------------------------
// Ending Screen Functions Declaration
//----------------------------------------------------------------------------------
void initEndingScreen(void);
void updateEndingScreen(void);
void drawEndingScreen(void);
void unloadEndingScreen(void);
int finishEndingScreen(void);


//----------------------------------------------------------------------------------
// Options Screen Functions Declaration
//----------------------------------------------------------------------------------
void initOptionsScreen(SettingsFile *sf);
void updateOptionsScreen(SettingsFile *sf);
void drawOptionsScreen(ResourcesState *rs);
void unloadOptionsScreen(void);
int finishOptionsScreen(void);

//----------------------------------------------------------------------------------
// Screen Transitions Functions Declaration
//----------------------------------------------------------------------------------
void TransitionToScreen(ScreenState *state, Screen toScreen);
void UpdateScreenTransition(ScreenState *state);
void DrawScreenTransition(WindowState *ws);

#endif