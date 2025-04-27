#include "raylib.h"
#include "states.h"

void updatePlayerMovement(MainState *ms, PlayerMovementState *pms)
{
    if (!ms->pause)
    {
        if (IsKeyDown(KEY_UP))
            pms->player.y -= pms->playerSpeed;
        else if (IsKeyDown(KEY_DOWN))
            pms->player.y += pms->playerSpeed;
        else if (IsKeyDown(KEY_RIGHT))
            pms->player.x += pms->playerSpeed;
        else if (IsKeyDown(KEY_LEFT))
            pms->player.x -= pms->playerSpeed;
    }
}
