#include "raylib.h"
#include "gameStateManager.h"
void MovePlayer(Rectangle *player, float playerSpeed)
{
    if (IsKeyDown(KEY_UP))
        player->y -= playerSpeed;
    else if (IsKeyDown(KEY_DOWN))
        player->y += playerSpeed;
    else if (IsKeyDown(KEY_RIGHT))
        player->x += playerSpeed;
    else if (IsKeyDown(KEY_LEFT))
        player->x -= playerSpeed;

    if (player->y <= 0)
        player->y = 0;
    else if ((player->y + player->height) >= GetScreenHeight())
        player->y = GetScreenHeight() - player->height;
}
void PauseGame(GameStateManager *gm)
{
    if (IsKeyPressed(KEY_P))
        gm->pause = !gm->pause;

    if (IsKeyPressed(KEY_ENTER))
        gm->currentScreen = 2;
}