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
extern "C" void __stdcall PauseMenu_Initialize_00422ab0(PauseUpdateView* state);
extern "C" void __stdcall PauseMenu_Update_00422c80(PauseUpdateView* state);
extern "C" void __stdcall ReplayMenu_Update_004236f0(PauseUpdateView* state);

#pragma code_seg(".text$01update")
int PauseUpdateView::Update() {
    switch (phase) {
    case 0:
        if (!(g_globals_flags & 0x20) &&
            ((g_input_keys_held & 8) || (g_app_flags & 0x10)) &&
            g_game->active_frame &&
            (g_game->active_frame->flags & 2) &&
            g_game->elapsed >= 30)
            PauseMenu_Initialize_00422ab0(this);
        break;
    case 1: case 2: case 3: case 4: case 5:
        PauseMenu_Update_00422c80(this);
        break;
    case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        ReplayMenu_Update_004236f0(this);
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
