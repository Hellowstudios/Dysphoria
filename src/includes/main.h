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
    ResourcesState *rs,
    MainState *ms,
    ScreenState *ss,
    WindowState *ws
);
bool FixedUpdate();
void InitTimeState(float fixedTimeStep);
#endif