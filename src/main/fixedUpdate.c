#include "states.h"
#include "raylib.h"
#include "player.h"
#include <stdbool.h>

static TimeState timeState;
void InitTimeState(float fixedTimeStep)  
{
    timeState =(TimeState) {
        .fixedTimeStep = fixedTimeStep, 
        .accumulator = 0.0f, 
    };
}
bool FixedUpdate()  // Only use this function for physics releated logics(ex. movement)
{
    timeState.accumulator += GetFrameTime();
    while(timeState.accumulator >= timeState.fixedTimeStep) 
    {
        timeState.accumulator -= timeState.fixedTimeStep;
        return true;
    }
    return false;
}