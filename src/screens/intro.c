#include "raylib.h"
#include "screens.h"
#include "states.h"
#include "player.h"
#include "camerasystem.h"
#include  <stdio.h>

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int numObjects = 4;  // At the top with other definitions

// Defines the next screen to go to
static int toScreen = -1;
static PlayerMovementState pms;
static Camera2D camera = {0};
static IntroScreenObjects isp;
static Rectangle map;
static Rectangle roomWall;
static Rectangle objects[4];

void initIntroScreen(ResourcesState *rs, WindowState *ws)
{
    rs->playerWalk1Texture = LoadTextureFromImage(LoadImage("resources/img/character/walk1.png"));
    rs->playerWalk2Texture = LoadTextureFromImage(LoadImage("resources/img/character/walk2.png"));
    rs->roomFloor = LoadTextureFromImage(LoadImage("resources/img/objects/wood-planks.png"));
    rs->roomWall = LoadTextureFromImage(LoadImage("resources/img/objects/wall.png"));
    rs->plant = LoadTextureFromImage(LoadImage("resources/img/objects/plant.png"));
    rs->plant2 = LoadTextureFromImage(LoadImage("resources/img/objects/plant2.png"));
    rs->plant3 = LoadTextureFromImage(LoadImage("resources/img/objects/plant3.png"));
    rs->plant4 = LoadTextureFromImage(LoadImage("resources/img/objects/plant4.png"));

    // position of map that will be drawn on the screen
    map = (Rectangle){0, rs->roomWall.height - rs->playerWalk1Texture.height, rs->roomFloor.width, rs->roomFloor.height};

    pms = (PlayerMovementState){
        .acceleration = 300,    // Reduced further for smoother acceleration
        .friction = 0.92f,    // Adjusted friction
        .notMoving = false,
        .player = {map.x + 20, map.y + 20, rs->playerWalk1Texture.width, rs->playerWalk1Texture.height},
        .maxSpeed = 200,
        .velocityX = 0,
        .velocityY = 0,
    };

    
    roomWall = (Rectangle){0, 0, rs->roomWall.width, rs->roomWall.height};

    // position of objects that will be drawn on the screen
    isp = (IntroScreenObjects){
        .plant = {map.width - 30, map.y + 20  , rs->plant.width, rs->plant.height - (pms.player.height / 3)},
        .plant2 = {map.width - 30, map.y + 40, rs->plant2.width, rs->plant2.height - (pms.player.height / 3)},
        .plant3 = {map.width - 30, map.y + 60, rs->plant3.width, rs->plant3.height - (pms.player.height / 3)},
        .plant4 = {map.width - 30, map.y + 80, rs->plant4.width, rs->plant4.height - (pms.player.height / 3)},
    };

    objects[0] = isp.plant;
    objects[1] = isp.plant2;
    objects[2] = isp.plant3;
    objects[3] = isp.plant4;
    
    // intialize camera
    camera.rotation = 0.0f;
    camera.zoom = 4;
    
    UpdateGameCamera(&camera, &pms, ws);
};

void updateIntroScreen(MainState *ms, WindowState *ws, ResourcesState *rs)
{
    UpdateGameCamera(&camera, &pms, ws);
    UpdatePlayerMovement(&pms, &map, objects, numObjects);

    if (IsKeyPressed(KEY_ENTER)) {
        initEndingScreen();
        toScreen = ENDING;
    }
};

void drawIntroScreen(ResourcesState *rs, MainState *ms)
{
    BeginMode2D(camera);

    DrawTexture(rs->roomFloor, map.x, map.y, WHITE);
    DrawTexture(rs->roomWall, roomWall.x, roomWall.y, WHITE);
    DrawTexture(rs->playerWalk1Texture, pms.player.x, pms.player.y, WHITE);
    DrawTexture(rs->plant, isp.plant.x, isp.plant.y, WHITE);
    DrawTexture(rs->plant2, isp.plant2.x, isp.plant2.y, WHITE);
    DrawTexture(rs->plant3, isp.plant3.x, isp.plant3.y, WHITE);
    DrawTexture(rs->plant4, isp.plant4.x, isp.plant4.y, WHITE);

    if (ms->pause)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.8f));
        DrawText("GAME PAUSED", 320, 200, 30, RED);
    }
    
    EndMode2D();
};

void unloadIntroScreen(ResourcesState *rs)
{
    UnloadTexture(rs->playerWalk1Texture);
    UnloadTexture(rs->playerWalk2Texture);
};

int finishIntroScreen()
{
    return toScreen;
};
