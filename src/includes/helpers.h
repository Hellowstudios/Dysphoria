#ifndef HELPERS_H
#define HELPERS_H

#include "states.h"

void InitilizeResources(ResourcesState *rs);
void updatePlayerMovement(MainState *ms, PlayerMovementState *pms);
void writeSettingsFile(SettingsFile *newSettingsFile);
SettingsFile *readSettingsFile(void);

#endif