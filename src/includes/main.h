#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include "states.h"

ResourcesState* initilizeResources(void);

void updateGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    SettingsFile *sf
);

void drawGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws
);

#endif