/**********************************************************************************************
 * This header file contains all the functions that are used to init, update, draw, unload, and finish the screens.
 **********************************************************************************************/

#ifndef SCREENS_H
#define SCREENS_H

//----------------------------------------------------------------------------------
// Maın Menu Screen Functions Declaration
//----------------------------------------------------------------------------------
void initMainMenuScreen(void);
void updateMainMenuScreen(void);
void drawMainMenuScreen(void);
void unloadMainMenuScreen(void);
void finishMainMenuScreen(void);

//----------------------------------------------------------------------------------
// Introduction Screen Functions Declaration
//----------------------------------------------------------------------------------
void initIntroScreen(void);
void updateIntroScreen(void);
void drawIntroScreen(void);
void unloadIntroScreen(void);
void finishIntroScreen(void);

#endif