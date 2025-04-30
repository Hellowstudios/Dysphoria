#include "raylib.h"
#include "states.h"

Camera2D InitCamera(int screenWidth, int screenHeight, PlayerMovementState *pms)
{
    Camera2D camera = {0};
    // Center on player by using player dimensions
    float playerCenterX = pms->player.x + pms->player.width/2;
    float playerCenterY = pms->player.y + pms->player.height/2;
    
    camera.target = (Vector2){playerCenterX, playerCenterY};   
    camera.offset = (Vector2){ screenWidth / 2, screenHeight/2 };
    camera.zoom = 3;
    camera.rotation = 0.0f;
    return camera;
}

void UpdateGameCamera(Camera2D *camera, PlayerMovementState *pms, WindowState *ws)   
{
    // Calculate target position (player's center)
    float playerCenterX = pms->player.x + pms->player.width/2;
    float playerCenterY = pms->player.y + pms->player.height/2;
    Vector2 targetPosition = (Vector2){ playerCenterX, playerCenterY };
    
    // Set smoothing factor (adjust this value between 0 and 1 to control smoothness)
    float smoothSpeed = 0.2f;
    
    // Smoothly interpolate between current camera target and new target position
    camera->target.x = camera->target.x + (targetPosition.x - camera->target.x) * smoothSpeed;
    camera->target.y = camera->target.y + (targetPosition.y - camera->target.y) * smoothSpeed;
    
    // Update camera offset based on screen dimensions
    camera->offset = (Vector2){ ws->screenWidth / 2, ws->screenHeight / 2 };
}