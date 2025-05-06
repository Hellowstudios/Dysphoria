#include <stdio.h>
#include "raylib.h"
#include "states.h"
#include <stdlib.h>

ResourcesState *initilizeResources() {
    ResourcesState *rs = malloc(sizeof(ResourcesState));

    *rs = (ResourcesState){
        .playerWalk1Texture = (Texture){0},
        .playerWalk2Texture = (Texture){0},
        .playerLeftWalk1Texture = (Texture){0},
        .playerLeftWalk2Texture = (Texture){0},
        .playerLeftWalk3Texture = (Texture){0},
        .playerRightWalk1Texture = (Texture){0},
        .playerRightWalk2Texture = (Texture){0},
        .playerRightWalk3Texture = (Texture){0},
        .mainFontSm = (Font){0},
        .mainFontMd = (Font){0},
        .roomFloor = (Texture){0},
    };

    rs->playerWalk1Texture = LoadTextureFromImage(LoadImage("resources/img/character/walk1.png"));

    rs->mainFontSm = LoadFontEx("resources/fonts/GloriaHallelujah-Regular.ttf", 40, NULL, 0xFFFF);
    SetTextureFilter(rs->mainFontSm.texture, TEXTURE_FILTER_BILINEAR); 

    rs->mainFontMd = LoadFontEx("resources/fonts/GloriaHallelujah-Regular.ttf", 120, NULL, 0xFFFF);
    SetTextureFilter(rs->mainFontMd.texture, TEXTURE_FILTER_BILINEAR);  

    return rs;
} 
