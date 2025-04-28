#ifndef SCREENS_H
#define SCREENS_H

#include "states.h"

//----------------------------------------------------------------------------------
// Main Menu Screen Functions Declaration
//----------------------------------------------------------------------------------
void initMainMenuScreen(void);
void updateMainMenuScreen(ScreenState *ss);
void drawMainMenuScreen(WindowState *ws, ResourcesState *rs);
void unloadMainMenuScreen(void);
int finishMainMenuScreen(void);

//----------------------------------------------------------------------------------
// Intro Screen Functions Declaration
//----------------------------------------------------------------------------------
void initIntroScreen(void);
void updateIntroScreen(MainState *ms, PlayerMovementState *pms);
void drawIntroScreen(ResourcesState *rs, MainState *ms, PlayerMovementState *pms);
void unloadIntroScreen(void);
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
void initOptionsScreen(void);
void updateOptionsScreen(void);
void drawOptionsScreen(ResourcesState *rs);
void unloadOptionsScreen(void);
int finishOptionsScreen(void);


//----------------------------------------------------------------------------------
// Screen Transitions Functions Declaration
//----------------------------------------------------------------------------------
void TransitionToScreen(ScreenState *state, Screen toScreen);
void UpdateScreenTransition(ScreenState *state);
void DrawScreenTransition(void);

#endif