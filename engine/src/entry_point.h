#pragma once

#include "core/application.h"
#include "core/glmemory.h"
#include "core/logger.h"
#include "game_types.h"

extern bool8 CreateGame(game* outGame);

// Main entry-point of application
int main(void) {
    
    Init_Memory();

    // Try to Create the Game
    game gameInst;
    if(!CreateGame(&gameInst)) {

        GL_FATAL("Could not create game!");
        return -1;
    } else  GL_TRACE("Created Game");

    // Make sure all function Pointers are set
    if(!gameInst.initialize || !gameInst.update || !gameInst.render || !gameInst.onResize) {

        GL_FATAL("The game's function pointers musst be assigned!");
        return -2;
    } else  GL_TRACE("The game's function pointers are all set");

    // Initialize
    if (!applicationCreate(&gameInst)) {
        
        GL_INFO("Application failed to create");
        return 1;
    } else  GL_TRACE("Application was created successfully");

    // Begin game loop
    if (!applicationRun()) {

        GL_INFO("Application did not shut down garacfully");
        return 2;
    } else  GL_TRACE("Application shut down garacfully");

    shutdown_Memory();
    
    return 0;
}