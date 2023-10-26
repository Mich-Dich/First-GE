#include "input.h"
#include "event.h"
#include "glmemory.h"
#include "logger.h"

typedef struct keyboard_State {
    bool8 keys[256];
} keyboard_State;

typedef struct mouse_State {
    int16 X;
    int16 Y;
    bool8 buttons[BU_MAX_BUTTONS];
} mouse_State;

typedef struct Input_State {
    keyboard_State keyboard_current;
    keyboard_State keyboard_previous;
    mouse_State mouse_current;
    mouse_State mouse_previous;
} Input_State;

static bool8 initialized = FALSE;
static Input_State state = {};



void Input_Init(){

    gl_zero_memory(&state, sizeof(Input_State));
    initialized = TRUE;
    GL_TRACE("Initializing subsystem [Input]");
}

void Input_Shutdown() {

    initialized = FALSE;
    GL_TRACE("Shuttingdown subsystem [Input]");
}

void Input_Update(double delta_time) {

    // basic savegard
    if (!initialized) {

        // GL_WARNING("Subsystem [Input] needs to be initalized befor [Input_Update] is called");
        return;
    }

    // copy current state to previous state
    gl_copy_memory(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboard_State));
    gl_copy_memory(&state.mouse_previous, &state.mouse_current, sizeof(keyboard_State));
}

void Input_process_key(keys key, bool8 pressed) {

    // only fire if state changes
    if (state.keyboard_current.keys[key] != pressed) {
        state.keyboard_current.keys[key] = pressed;

        // Fire Event
        eventContext context;
        context.data.u16[0] = key;
        event_fire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0, context);
    }
}

void Input_process_button(buttons button, bool8 pressed) {

    // only fire if state changes
    if (state.mouse_current.buttons[button] != pressed) {
        state.mouse_current.buttons[button] = pressed;

        // Fire Event
        eventContext context;
        context.data.u16[0] = button;
        event_fire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, context);
    }
}

void Input_process_mouse_move(int16 x, int16 y) {

    // only fire if state changes
    if (state.mouse_current.X != x || state.mouse_current.Y != y) {
        state.mouse_current.X = x;
        state.mouse_current.Y = y;

        GL_DEBUG("Mouse Pos [X: %i, Y: %i]", x, y);

        // Fire Event
        eventContext context;
        context.data.u16[0] = x;
        context.data.u16[1] = y;
        event_fire(EVENT_CODE_MOUSE_MOVED, 0, context);
    }
}

void Input_process_mouse_wheel(int8 z_delta) {

    // Fire Event
    eventContext context;
    context.data.u8[0] = z_delta;
    event_fire(EVENT_CODE_MOUSE_WHEEL, 0, context);
}



// keyboard input
bool8 Input_is_key_down(keys key) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_is_key_down] needs subsystem [Input] to be initialized");
        return FALSE;
    }

    return state.keyboard_current.keys[key] == TRUE;
}

bool8 Input_is_key_up(keys key) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_is_key_up] needs subsystem [Input] to be initialized");
        return TRUE;
    }

    return state.keyboard_current.keys[key] == FALSE;
}

bool8 Input_was_key_down(keys key) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_was_key_down] needs subsystem [Input] to be initialized");
        return FALSE;
    }

    return state.keyboard_previous.keys[key] == TRUE;
}

bool8 Input_was_key_up(keys key) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_was_key_up] needs subsystem [Input] to be initialized");
        return TRUE;
    }

    return state.keyboard_previous.keys[key] == FALSE;
}

// mouse input
bool8 Input_is_button_down(buttons button) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_is_button_down] needs subsystem [Input] to be initialized");
        return FALSE;
    }

    return state.mouse_current.buttons[button] == TRUE;
}

bool8 Input_is_button_up(buttons button) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_is_button_up] needs subsystem [Input] to be initialized");
        return TRUE;
    }

    return state.mouse_current.buttons[button] == FALSE;
}

bool8 Input_was_button_down(buttons button) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_was_button_down] needs subsystem [Input] to be initialized");
        return FALSE;
    }

    return state.mouse_previous.buttons[button] == TRUE;
}

bool8 Input_was_button_up(buttons button) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_was_button_up] needs subsystem [Input] to be initialized");
        return TRUE;
    }

    return state.mouse_previous.buttons[button] == FALSE;
}

void Input_get_mouse_position(int32* x, int32* y) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_get_mouse_position] needs subsystem [Input] to be initialized");
        *x = 0;
        *y = 0;
        return;
    }

    *x = state.mouse_current.X;
    *y = state.mouse_current.Y;
}

void Input_get_previous_mouse_position(int32* x, int32* y) {

    // basic savegard
    if (!initialized) {
        GL_WARNING("[Input_get_previous_mouse_position] needs subsystem [Input] to be initialized");
        *x = 0;
        *y = 0;
        return;
    }

    *x = state.mouse_previous.X;
    *y = state.mouse_previous.Y;
}
