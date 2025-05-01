#include "raylib.h"
#include "states.h"
#include <stdio.h>
#include <math.h>

int count = 0;

void UpdatePlayerMovement(PlayerMovementState *pms, Rectangle *map, Rectangle objects[], int objectCount)
{
    float deltaTime = GetFrameTime();
    printf("Delta time: %f\n", deltaTime);

    bool isUp = IsKeyDown(KEY_UP);
    bool isDown = IsKeyDown(KEY_DOWN);
    bool isRight = IsKeyDown(KEY_RIGHT);
    bool isLeft = IsKeyDown(KEY_LEFT);

    // Prevent right+up and left+down combinations
    if (!(isRight && isUp) && !(isLeft && isUp) && !(isLeft && isDown) && !(isRight && isDown))
    {
        // Apply acceleration based on input
        if (isUp) {
            pms->velocityY -= pms->acceleration *deltaTime;
            pms->notMoving = false;
        } if (isDown) {
            pms->velocityY += pms->acceleration * deltaTime;
            pms->notMoving = false;
        } if (isRight) {
            pms->velocityX += pms->acceleration * deltaTime;
            pms->notMoving = false;
        } if (isLeft) {
            pms->velocityX -= pms->acceleration * deltaTime;
            pms->notMoving = false;
        }
    }
    
    // Apply friction
    float adjustedFriction = pow(pms->friction, deltaTime * 60.0f);
    pms->velocityX *= adjustedFriction;
    pms->velocityY *= adjustedFriction;

    // Round very small velocities to 0 to prevent trembling
    if (fabs(pms->velocityX) < 1) pms->velocityX = 0;
    if (fabs(pms->velocityY) < 1) pms->velocityY = 0;

    // Set notMoving when both velocities are zero
    if (pms->velocityX == 0 && pms->velocityY == 0) {
        pms->notMoving = true;
    }
    
    // Cap maximum speed
    if (pms->velocityX > pms->maxSpeed * deltaTime) pms->velocityX = pms->maxSpeed * deltaTime;
    if (pms->velocityX < -pms->maxSpeed * deltaTime) pms->velocityX = -pms->maxSpeed * deltaTime;
    if (pms->velocityY > pms->maxSpeed * deltaTime) pms->velocityY = pms->maxSpeed * deltaTime;
    if (pms->velocityY < -pms->maxSpeed * deltaTime) pms->velocityY = -pms->maxSpeed * deltaTime;

    Rectangle playerNext = {
        .x = pms->player.x + pms->velocityX,
        .y = pms->player.y + pms->velocityY,
        .width = pms->player.width,
        .height = pms->player.height
    };

 // Add these debug prints before the loop
    printf("\n--- Starting collision checks ---\n");
    printf("Player position: %f, %f\n", playerNext.x, playerNext.y);
    printf("Object count: %d\n", objectCount);
    printf("First object address: %p\n", (void*)&objects[0]);
    
    // Print all object positions before the loop
    printf("\nInitial object positions:\n");
    for (int i = 0; i < objectCount; i++) {
        printf("Object %d: x=%f, y=%f, w=%f, h=%f\n", 
               i, objects[i].x, objects[i].y, objects[i].width, objects[i].height);
    }

    // Then in your collision check loop
    for (short i = 0; i < objectCount; i++)
    {
        printf("\nCollision check iteration %d:\n", i);
        printf("Checking object at address: %p\n", (void*)&objects[i]);
        printf("Object %d position: x=%f, y=%f, w=%f, h=%f\n", 
               i, objects[i].x, objects[i].y, objects[i].width, objects[i].height);
        
        bool collision = (playerNext.x < (objects[i].x + objects[i].width) && 
                         (playerNext.x + playerNext.width) > objects[i].x) &&
                        (playerNext.y < (objects[i].y + objects[i].height) && 
                         (playerNext.y + playerNext.height) > objects[i].y);
        
        if (collision) {
            printf("Collision detected with object %d\n", i);
            return;
        }
    }
    
    // Map collision check
    if (!((map->x < ((playerNext.x - pms->player.width) + pms->player.width) && 
            (map->x + map->width) > (playerNext.x + pms->player.width)) &&
            (map->y < ((playerNext.y - pms->player.height) + pms->player.height) && 
            (map->y + map->height) > (playerNext.y + pms->player.height)))) return;

    // Update position
    pms->player.x = playerNext.x;
    pms->player.y = playerNext.y;
}