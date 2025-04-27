#include <stdbool.h>
typedef enum
{
    MAIN_MENU = 0,
    INTRO,
    ENDING,
} GameScreen;

typedef struct
{
    GameScreen currentScreen;
    bool pause;
    bool finishGame;
} GameStateManager;

GameStateManager ConstructGameStateManager();