#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "raylib.h"
#include "states.h"

void UpdateGameCamera(Camera2D *camera, PlayerMovementState *pms, WindowState *ws);

#endif