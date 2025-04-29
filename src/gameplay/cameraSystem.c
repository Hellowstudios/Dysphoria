#include "raylib.h"
#include "states.h"
#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

Camera2D InitCamera(int screenWidth, int screenHeight, PlayerMovementState *pms)
{
    Camera2D camera = {0};
    camera.target = (Vector2){pms->player.x + 20, pms->player.y + 20};   
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    return camera;
}

void UpdateGameCamera(Camera2D *camera, PlayerMovementState *pms)   
{
    camera->target = (Vector2){pms->player.x + 20, pms->player.y + 20};
}

#endif
