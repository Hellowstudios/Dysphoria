#include "raylib.h"
#include "states.h"
Camera2D InitCamera(int screenWidth, int screenHeight, PlayerMovementState *pms);
void UpdateaCamera(Camera2D *camera,PlayerMovementState *pms);