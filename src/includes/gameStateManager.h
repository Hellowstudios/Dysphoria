#include <stdbool.h>
typedef enum
{
    SCREEN_TITLE = 0,
    SCREEN_GAMEPLAY,
    SCREEN_ENDING
} GameScreen;

typedef struct
{
    GameScreen currentScreen;
    bool pause;
    bool finishGame;
} GameStateManager;

GameStateManager ConstructGameStateManager(GameStateManager gm);