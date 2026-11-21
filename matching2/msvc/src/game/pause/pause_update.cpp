// 0x004223F0: dispatch the pause/replay menu phase and advance its frame timer.
// 0x00422A90: the scheduler callback registered by the menu's task installer.
//
// Phase zero enters the pause menu only when the game permits it and the
// active game frame has reached frame 30. The remaining phases update the
// pause menu (1..5) or replay menu (6..13). The timer treats speeds near one
// as a single frame; other speeds accumulate before conversion to an integer.
// Native LTCG derives the Update receiver in ESI from the complete routine
// and its actual scheduler callback. Both complete contributions, including
// Update's switch tables, are byte exact without a synthetic caller.

struct PauseMenuFrame {
    unsigned int unused;
    unsigned char flags;
};
struct PauseMenuRuntime {
    unsigned char unknown_00[8];
    PauseMenuFrame* active_frame;
    unsigned char unknown_0c[8];
    int elapsed;
};
extern "C" unsigned char g_globals_flags;
extern "C" unsigned char g_input_keys_held;
extern "C" unsigned char g_app_flags;
extern "C" PauseMenuRuntime* g_game;
extern "C" float flt_0_99;
extern "C" float flt_1_01;

struct PauseUpdateView {
    int unknown_00;
    unsigned int phase;
    unsigned char unknown_08[8];
    int previous_frame;
    int current_frame;
    float elapsed;
    const float* speed;
    __declspec(noinline) int Update();
};
extern "C" void __stdcall PauseMenu_Initialize(PauseUpdateView* state);
extern "C" void __stdcall PauseMenu_Update(PauseUpdateView* state);
extern "C" void __stdcall ReplayMenu_Update(PauseUpdateView* state);

enum PauseDispatchPhase {
    PAUSE_CLOSED = 0,
    PAUSE_OPENING = 1,
    PAUSE_MENU = 2,
    PAUSE_CLOSING = 3,
    PAUSE_CONFIRM_OPEN = 4,
    PAUSE_CONFIRM_RESOLVE = 5,
    SUBMENU_WAIT_ENTRY = 6,
    SUBMENU_SETUP_SCORE = 7,
    SUBMENU_SAVE_CHOICE = 8,
    SUBMENU_STATE_9 = 9,
    SUBMENU_REPLAY_BROWSER = 10,
    SUBMENU_REPLAY_NAME_EDITOR = 11,
    SUBMENU_SCORE_NAME_EDITOR = 12,
    SUBMENU_FINAL_EXIT = 13
};

enum PauseDispatchFlags {
    PAUSE_GLOBAL_FLAG_DEMO = 0x20,
    PAUSE_KEY_ESC = 0x08,
    PAUSE_APP_FLAG_LOST_FOCUS = 0x10,
    PAUSE_FRAME_ACTIVE_FLAG = 0x02
};

#pragma code_seg(".text$01update")
int PauseUpdateView::Update() {
    switch (phase) {
    case PAUSE_CLOSED:
        if (!(g_globals_flags & PAUSE_GLOBAL_FLAG_DEMO) &&
            ((g_input_keys_held & PAUSE_KEY_ESC) || (g_app_flags & PAUSE_APP_FLAG_LOST_FOCUS)) &&
            g_game->active_frame &&
            (g_game->active_frame->flags & PAUSE_FRAME_ACTIVE_FLAG) &&
            g_game->elapsed >= 30)
            PauseMenu_Initialize(this);
        break;
    case PAUSE_OPENING: case PAUSE_MENU: case PAUSE_CLOSING:
    case PAUSE_CONFIRM_OPEN: case PAUSE_CONFIRM_RESOLVE:
        PauseMenu_Update(this);
        break;
    case SUBMENU_WAIT_ENTRY: case SUBMENU_SETUP_SCORE: case SUBMENU_SAVE_CHOICE:
    case SUBMENU_STATE_9: case SUBMENU_REPLAY_BROWSER: case SUBMENU_REPLAY_NAME_EDITOR:
    case SUBMENU_SCORE_NAME_EDITOR: case SUBMENU_FINAL_EXIT:
        ReplayMenu_Update(this);
        break;
    }
    previous_frame = current_frame;
    if (*speed > flt_0_99 && *speed < flt_1_01) {
        ++current_frame;
        elapsed += 1.0f;
    } else {
        elapsed = *speed + elapsed;
        current_frame = (int)elapsed;
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$03callback")
__declspec(noinline) int __fastcall Pause_OnUpdate(PauseUpdateView* state) {
    return state->Update();
}
#pragma code_seg()
