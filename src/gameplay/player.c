#include "raylib.h"
#include "states.h"
#include <stdio.h>
#include <math.h>

int count = 0;

void UpdatePlayerMovement(MainState *ms, PlayerMovementState *pms, ResourcesState *rs)
{
   if (!ms->pause)
    {
        bool isUp = IsKeyDown(KEY_UP);
        bool isDown = IsKeyDown(KEY_DOWN);
        bool isRight = IsKeyDown(KEY_RIGHT);
        bool isLeft = IsKeyDown(KEY_LEFT);

        // Prevent right+up and left+down combinations
        if (!(isRight && isUp) && !(isLeft && isUp) && !(isLeft && isDown) && !(isRight && isDown))
        {
            // Apply acceleration based on input
            if (isUp) {
                pms->velocityY -= pms->acceleration;
                pms->notMoving = false;
            }
            if (isDown) {
                pms->velocityY += pms->acceleration;
                pms->notMoving = false;
            }
            if (isRight) {
                pms->velocityX += pms->acceleration;
                pms->notMoving = false;
            }
            if (isLeft) {
                pms->velocityX -= pms->acceleration;
                pms->notMoving = false;
            }
        }

        
        // Apply friction
        pms->velocityX *= pms->friction;
        pms->velocityY *= pms->friction;

        // Round very small velocities to 0 to prevent trembling
        if (fabs(pms->velocityX) < 0.5f) pms->velocityX = 0;
        if (fabs(pms->velocityY) < 0.5f) pms->velocityY = 0;

        // Set notMoving when both velocities are zero
        if (pms->velocityX == 0 && pms->velocityY == 0) {
            pms->notMoving = true;
        }
        
        // Cap maximum speed
        if (pms->velocityX > pms->maxSpeed) pms->velocityX = pms->maxSpeed;
        if (pms->velocityX < -pms->maxSpeed) pms->velocityX = -pms->maxSpeed;
        if (pms->velocityY > pms->maxSpeed) pms->velocityY = pms->maxSpeed;
        if (pms->velocityY < -pms->maxSpeed) pms->velocityY = -pms->maxSpeed;

        // Boundary check
        if (!((0 < (((pms->player.x + pms->velocityX) - pms->player.width) + pms->player.width) && 
              (0 + rs->room.width) > ((pms->player.x + pms->velocityX) + pms->player.width)) &&
              (0 < (((pms->player.y + pms->velocityY) - pms->player.height) + pms->player.height) && 
              (0 + rs->room.height) > ((pms->player.y + pms->velocityY) + pms->player.height)))) return;

        // Update position
        pms->player.x += pms->velocityX;
        pms->player.y += pms->velocityY;
    }
}