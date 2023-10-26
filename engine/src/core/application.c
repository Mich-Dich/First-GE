#include "application.h"
#include "game_types.h"
#include "platform/platform.h"

#include "core/logger.h"
#include "core/glmemory.h"
#include "core/event.h"
#include "core/input.h"

typedef struct applicationState {
    game* gameInst;
    bool8 isRunning;
    bool8 isSuspended;
    platformState platform;
    int16 width;
    int16 height;
    double lastTime;
} applicationState;

static bool8 initialized = FALSE;
static applicationState AppState;

bool8 application_on_event(u16 code, void* sender, void* listener_inst, eventContext context);
bool8 application_on_key(u16 code, void* sender, void* listener_inst, eventContext context);

bool8 applicationCreate(game* gameInst) {

    // Savegard abainst mulltiple Creates
    if (initialized) {
        GL_ERROR("applicationCate() called more than once");
        return FALSE;
    }

    AppState.gameInst = gameInst;

    // Initialize subsystems
    Log_Init();
    Input_Init();

    AppState.isRunning = TRUE;
    AppState.isSuspended = FALSE;

    // Initalize Event System
    if (!event_Init()) {

        GL_ERROR("Event system failed to initalize. suttingdown appliaction");
        return FALSE;
    }

    // Initalize platform
    if (!platform_Startup(
        &AppState.platform,
        gameInst->AppConfic.name, 
        gameInst->AppConfic.statPosX, 
        gameInst->AppConfic.statPosY, 
        gameInst->AppConfic.statWidth, 
        gameInst->AppConfic.statHeight)) {

            return FALSE;
    }
    
    if (!AppState.gameInst->initialize(AppState.gameInst)) {

        GL_FATAL("Game Failed to Initialize");
        return FALSE;
    }

    AppState.gameInst->onResize(AppState.gameInst, AppState.width, AppState.height);
    initialized = TRUE;
    return TRUE;
}

bool8 applicationRun() {

    GL_INFO(get_memory_usage_str());

    // Main game loop
    while(AppState.isRunning) {

        if (!platform_Push_messages(&AppState.platform)) 
            AppState.isRunning = FALSE;

        if (!AppState.isSuspended) {
            
            // Call games update routine
            if(!AppState.gameInst->update(AppState.gameInst, (float)0)) {

                // Handle errors
                GL_FATAL("Game update failed, Shutting down");
                AppState.isRunning = FALSE;
                break;
            }
            
            // Call games render routine
            if(!AppState.gameInst->render(AppState.gameInst, (float)0)) {

                // Handle errors
                GL_FATAL("Game render failed, Shutting down");
                AppState.isRunning = FALSE;
                break;
            }

            // NOTE: Input update/state copying should always be handled
            // after any input should be recorded; I.E. before this line.
            // As a safety, input is the last thing to be updated before
            // this frame ends.
            // Input_Update(0);
        }
        
    }

    // make sure [isRunning] is set to false. 
    AppState.isRunning = FALSE;

    // Shutdown game loop
    platform_Shutdown(&AppState.platform);
    event_Shutdown();
    Input_Shutdown();
    Log_Shutdown();
    return TRUE;
} 

bool8 application_on_event(u16 code, void* sender, void* listener_inst, eventContext context) {

    switch (code) {
        case EVENT_CODE_APPLICATION_QUIT: {

            GL_INFO("Code [EVENT_CODE_APPLICATION_QUIT] recived, shutting down\n");
            AppState.isRunning = FALSE;
            return TRUE;
        }
    }

    return FALSE;
}

bool8 application_on_key(u16 code, void* sender, void* listener_inst, eventContext context) {

    if (code == EVENT_CODE_KEY_PRESSED) {

        u16 key_code = context.data.u16[0];
        if (key_code == KEY_ESCAPE) {

            // NOTE: Technically firing an event to itself, but there may be other listeners.
            eventContext data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

            // Block anything else from processing this.
            return TRUE;
        } 
        
        else if (key_code == KEY_A) {
            // Example on checking for a key
            GL_DEBUG("Explicit - A key pressed!");
        } 
        
        else {
            GL_DEBUG("'%c' key pressed in window.", key_code);
        }

    } else if (code == EVENT_CODE_KEY_RELEASED) {

        u16 key_code = context.data.u16[0];
        if (key_code == KEY_B) {
            // Example on checking for a key
            GL_DEBUG("Explicit - B key released!");
        } 
        
        else {
            GL_DEBUG("'%c' key released in window.", key_code);
        }
    }

    return FALSE;
}