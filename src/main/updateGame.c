
#include <stdio.h>
#include "raylib.h"
#include "states.h"

void updateGame(
    MainState *ms,
    ResourcesState *rs,
    ScreenState *ss,
    WindowState *ws,
    SettingsFile *sf
) {
    if (!ss->onTransition)
    {
        switch (ss->currentScreen)
        {
            case MAIN_MENU:
            {
                updateMainMenuScreen(ss, sf, rs, ws);
                
                int nextScreen = finishMainMenuScreen();
                if (nextScreen != -1)
                {
                    TransitionToScreen(ss, nextScreen);
                    unloadMainMenuScreen();
                }
            } break; 
            case OPTIONS:
            {
                updateOptionsScreen(sf);
                
                int nextScreen = finishOptionsScreen();
                if (nextScreen != -1)
                {
                    TransitionToScreen(ss, nextScreen);
                    unloadOptionsScreen();
                }
            } break;        
            case INTRO:
            {
                updateIntroScreen(ms, ws, rs);

                int nextScreen = finishIntroScreen();
                if (nextScreen != -1)                {
                    TransitionToScreen(ss, nextScreen);
                    unloadIntroScreen(rs);
                }
            } break;
            case ENDING:
            {
                updateEndingScreen();

                int nextScreen = finishEndingScreen();
                if (nextScreen != -1)
                {
                    TransitionToScreen(ss, nextScreen);
                    unloadEndingScreen();
                }
            } break;
        } 
    }
    else 
        UpdateScreenTransition(ss);
}
