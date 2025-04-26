#include "gameStateManager.h"
GameStateManager ConstructGameStateManager(GameStateManager gm)
{
    gm.currentScreen = SCREEN_TITLE;
    gm.finishGame = false;
    gm.pause = false;
    return gm;
}