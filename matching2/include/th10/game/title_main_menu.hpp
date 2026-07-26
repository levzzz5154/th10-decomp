#pragma once

#include <cstdint>

enum TitleMenuInput : uint32_t {
    TITLE_MENU_UP = 0x10,
    TITLE_MENU_DOWN = 0x20,
    TITLE_MENU_CANCEL = 0x0A,
    TITLE_MENU_CONFIRM = 0x1001,
};

enum TitleMenuAction {
    TITLE_MENU_ACTION_NONE = 0,
    TITLE_MENU_ACTION_START,
    TITLE_MENU_ACTION_EXTRA,
    TITLE_MENU_ACTION_PRACTICE,
    TITLE_MENU_ACTION_REPLAY,
    TITLE_MENU_ACTION_MUSIC_ROOM,
    TITLE_MENU_ACTION_RESULTS,
    TITLE_MENU_ACTION_OPTIONS,
    TITLE_MENU_ACTION_QUIT,
};

// Retail keeps this inline in the title object; the dword indices are the
// ones 0x0042D420 and 0x0044BEA0 use, relative to that object.
struct TitleMainMenuState {
    int phase;               // a3[8]
    int selection;           // a3[9]
    int previous_selection;  // a3[10]
    int item_count;          // a3[11]
    int phase_frame;         // a3[173]
    TitleMenuAction pending_action;
    // 0x0044BEA0 reads these while moving the cursor.
    int wrap;                // a3[61]: 0 clamps at the ends, non-zero wraps
    int unavailable[16];     // a3[45..]: entries the cursor steps over
    int unavailable_count;   // a3[62]
};

// The edges 0x0042D420 takes that are not the caller's business to inline.
// Retail performs each of these directly; they are injected so the menu logic
// itself stays a transcription.
struct TitleMainMenuEnv {
    void* context;
    // sub_43DC90(dword_492590, id, 0): 12 = cursor moved, 11 = cancel,
    // 10 = confirm.
    void (*play_sound)(void* context, int id);
    // sub_42C770(a3, script, interrupt).
    void (*broadcast)(void* context, int script, int interrupt);
    // sub_42C750(a3, script), which is AnimationManager_SetStopFrameAndRun
    // (0x00449250) with interrupt 3: broadcast it to that script's VMs and
    // tick them in the same call rather than on the next frame.
    void (*broadcast_and_run)(void* context, int script, int interrupt);
    // sub_42C850: false marks the Extra entry unselectable.
    int (*extra_unlocked)(void* context);
    // DAT_00474CA0 bit 0x10, consumed and cleared by phase 0.
    int (*take_practice_flag)(void* context);
};

void TitleMainMenu_Initialize(TitleMainMenuState* state);
// Retail 0x0042D420. `env` may be null, in which case the edges are skipped
// and only the state machine runs.
TitleMenuAction TitleMainMenu_Update(TitleMainMenuState* state,
                                     uint32_t input_flags,
                                     const TitleMainMenuEnv* env);

// Retail 0x0044BEA0. Steps the cursor by `delta`, wrapping or clamping per
// `wrap`, and stepping over anything listed in `unavailable`.
void TitleMainMenu_MoveSelection(TitleMainMenuState* state, int delta);
