#include "event.h"
#include "glmemory.h"
#include "../containers/darray.h"
#include "logger.h"

typedef struct registeredEvent {
    void* lisener;
    PFN_On_Event callback;
} registeredEvent;

typedef struct eventCodeEntry {
    registeredEvent* events;
} eventCodeEntry;

// Define Max number of message codes, should be more than enotgh
#define MAX_MESSAGE_CODES 16384

typedef struct eventSystemState {
    eventCodeEntry registered[MAX_MESSAGE_CODES];
} eventSystemState;

static bool8 initalized = FALSE;
static eventSystemState state;

bool8 event_Init() {

    // Savegard against multiple Inits
    if (initalized == TRUE) 
        return FALSE;
    
    gl_zero_memory(&state, sizeof(state));
    initalized = TRUE;

    return TRUE;
}

void event_Shutdown() {

    // Free the events array
    for (u16 x = 0; x < MAX_MESSAGE_CODES; x++) {

        if (state.registered[x].events != 0) {

            darray_Destroy(state.registered[x].events);
            state.registered[x].events = 0;
        }        
    }
}

bool8 event_register(u16 code, void* listener, PFN_On_Event on_event) {

    // EventSystem must be registered
    if (initalized == FALSE) {

        // GL_ERROR("[event_register] called bevor event system is initalized");
        return FALSE;
    }

    if (state.registered[code].events == 0) 
        state.registered[code].events = darray_Create(registeredEvent);
    
    // listeners can only be registerd once
    u64 registerd_Count = darray_length(state.registered[code].events);
    for (u64 x = 0; x < registerd_Count; x++) {
        if (state.registered[code].events[x].lisener == listener) {

            // GL_WARNING("[event_register] listeners can only be registered once listener: %i was previously registered at [index: %i event: %i]", (u64)listener, code, x);
            return FALSE;
        }
    }

    // create listener event and set it in array
    registeredEvent event;
    event.lisener = listener;
    event.callback = on_event;
    darray_push(state.registered[code].events, event);

    return TRUE;
}

bool8 event_unregister(u16 code, void* listener, PFN_On_Event on_event) {

    // EventSystem must be registered
    if (initalized == FALSE) {

        GL_ERROR("[event_register] called bevor event system is initalized");
        return FALSE;
    }

    // Savegard against enpty array
    if (state.registered[code].events == 0) {
        
        GL_WARNING("[event_unregister] no listener registered for [code: %i]", code);
        return FALSE;
    }

    // Loop over events and pop if found
    u64 registerd_Count = darray_length(state.registered[code].events);
    for (u64 x = 0; x < registerd_Count; x++) { 
        
        // pop event if found
        registeredEvent loc_event = state.registered[code].events[x];
        if (loc_event.lisener == listener && loc_event.callback == on_event) {

            darray_pop_at(state.registered[code].events, x, &loc_event);
            return TRUE;
        }
    }

    // handle (Event not found)
    return FALSE;
}

bool8 event_fire(u16 code, void* sender, eventContext context) {

    // EventSystem must be registered
    if (initalized == FALSE) {

        GL_ERROR("[event_fire] called bevor event system is initalized");
        return FALSE;
    }

    // Savegard against enpty array
    if (state.registered[code].events == 0) {
        
        // GL_WARNING("[event_fire] no listener registered for [code: %i]", code);
        return FALSE;
    }
    
    // Loop over events and fire if found
    u64 registerd_Count = darray_length(state.registered[code].events);
    for (u64 x = 0; x < registerd_Count; x++) { 
        
        // fire event if listener handels event
        registeredEvent loc_event = state.registered[code].events[x];
        if (loc_event.callback(code, sender, loc_event.lisener, context))
            return TRUE;
        
    }
    
    // handle (Event not found)
    return FALSE;
}