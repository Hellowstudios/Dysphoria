#ifndef SCREENS_H
#define SCREENS_H

#include "states.h"

//----------------------------------------------------------------------------------
// Main Menu Screen Functions Declaration
//----------------------------------------------------------------------------------
void initMainMenuScreen(void);
void updateMainMenuScreen(void);
void drawMainMenuScreen(WindowState *ws);
void unloadMainMenuScreen(void);
int finishMainMenuScreen(void);

//----------------------------------------------------------------------------------
// Intro Screen Functions Declaration
//----------------------------------------------------------------------------------
void initIntroScreen(ResourcesState *rs);
void updateIntroScreen(MainState *ms, PlayerMovementState *pms);
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
// Screen Transitions Functions Declaration
//----------------------------------------------------------------------------------
void TransitionToScreen(ScreenState *state, Screen toScreen);
void UpdateScreenTransition(ScreenState *state);
void DrawScreenTransition(void);

#endif