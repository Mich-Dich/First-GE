#include "game.h"
#include <entry_point.h>
#include <core/glmemory.h>

// Define func to create game
bool8 CreateGame(game* outGame) {

    outGame->AppConfic.statPosX = 100;
    outGame->AppConfic.statPosY = 100;
    outGame->AppConfic.statWidth = 1280;
    outGame->AppConfic.statHeight = 720;
    outGame->AppConfic.name = "Gluttony Test Window";
    outGame->update = gameUpdate;
    outGame->render = gameRender;
    outGame->initialize = gameInitialize;
    outGame->onResize = gameOnResize;

    outGame->state = gl_allocate(sizeof(gameState), MEMORY_TAG_GAME);

    return TRUE;
}