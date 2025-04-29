#include "raylib.h"
#include <stdio.h>
#include "helpers.h"
#include "states.h"

//----------------------------------------------------------------------------------
// Does all the necessary cleanup before closing the window and exiting the program.
//----------------------------------------------------------------------------------
void closeWindow(SettingsFile *sf) {
    printf("Cleaning up...\n");
    writeSettingsFile(sf);
    CloseAudioDevice();
    printf("Cleaned up\n");
    CloseWindow(); // Close window and OpenGL context
};