#pragma once

#include <cstdint>

// Practice-stage picker state used by retail 0x00430FF0.  The dispatcher
// supplies the menu object on the stack; the function itself only consumes the
// object pointer and preserves the caller's register-bound menu context.
struct PracticeStageMenuState {
    int phase;
    int selection;
    int previous_selection;
    int selection_count;
    int phase_timer;
};

struct PracticeStageMenuEnv {
    uint32_t held;
    uint32_t pressed;
    int remembered_selection;
    int character;
    int shot;
    int difficulty;
    const uint8_t* stage_unlocks; // six bytes, one per practice stage
    const int8_t* direct_keys;    // nine signed DirectInput key bytes
    const int8_t* fallback_keys;  // nine bytes when direct polling fails
    bool direct_poll_succeeded;

    int selected_stage;
    int game_mode;
    int launch_state;
    int shortcut_stage;
};

struct PracticeStageMenuOps {
    void* context;
    void (*reset_view)(void*);
    void (*open_view)(void*, int);
    void (*close_view)(void*, int);
    void (*set_phase)(void*, int);
    void (*move_selection)(void*, PracticeStageMenuState*, int);
    void (*play_sound)(void*, int);
    void (*start_fade)(void*, float, float);
    void (*launch_stage)(void*, float);
};

// Semantic reconstruction of 0x00430FF0.
int PracticeStageMenu_Update(PracticeStageMenuState* state,
                             PracticeStageMenuEnv* env,
                             const PracticeStageMenuOps* ops);
