#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "raylib.h"
#include "states.h"

Camera2D InitCamera(int screenWidth, int screenHeight, PlayerMovementState *pms);
void UpdateGameCamera(Camera2D *camera, PlayerMovementState *pms);

#endif