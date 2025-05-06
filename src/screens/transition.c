
#include "states.h"
#include "raylib.h"

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;
static int framesCounter = 0;

// Request transition to next screen
void TransitionToScreen(ScreenState *state, Screen toScreen)
{
    state->onTransition = true;
    transFromScreen = state->currentScreen;
    transToScreen = toScreen;
}

// Update transition effect
void UpdateScreenTransition(ScreenState *state)
{
    float deltaTime = GetFrameTime() * 60;
    if (!transFadeOut)
    {        
        transAlpha += 0.02f * deltaTime;

        if (transAlpha >= 1.0)
        {
            transAlpha = 1.0;
            state->currentScreen = transToScreen;
            transFadeOut = true;
            framesCounter = 0;
        }
    }
    else // Transition fade out logic
    {
        transAlpha -= 0.02f * deltaTime;

        if (transAlpha <= 0)
        {
            transAlpha = 0;
            transFadeOut = false;
            state->onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void DrawScreenTransition(WindowState *ws)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, transAlpha));
}