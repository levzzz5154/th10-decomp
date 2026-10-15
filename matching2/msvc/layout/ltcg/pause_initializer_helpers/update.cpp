#include "th10/game/pause_initializer_00422ab0.hpp"
#pragma code_seg(".text$04update")
int PauseUpdateView::Update() {
    switch (phase) {
    case 0:
        if (!(data_00474ca0 & 0x20) &&
            ((data_00474e36 & 8) || (data_00491ff4 & 0x10)) &&
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
    if (*speed > data_00470b68 && *speed < data_00470b64) {
        ++current_frame;
        elapsed += 1.0f;
    } else {
        elapsed = *speed + elapsed;
        current_frame = (int)elapsed;
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$05callback")
__declspec(noinline) int __fastcall Pause_OnUpdate(PauseUpdateView* state) {
    return state->Update();
}
#pragma code_seg()
