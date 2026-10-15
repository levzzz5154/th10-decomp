#define g_sprt_ctrl stage_effect_g_sprt_ctrl
#define g_front stage_effect_g_front
#define data_00474c40 stage_effect_data_00474c40
#define g_ascii_manager stage_effect_data_004776e0
#define g_enemy_ctrl stage_effect_g_enemy_ctrl
#define g_player stage_effect_data_00477834
#define data_00477838 stage_effect_data_00477838
#define data_0047783c stage_effect_data_0047783c
#define data_00476f78 stage_effect_data_00476f78
#define data_00491fc4 stage_effect_data_00491fc4
#define data_00491fb8 stage_effect_data_00491fb8
#define data_00492590 stage_effect_data_00492590
#include "th10/core/screen.hpp"

#pragma code_seg(".text$0043c8b0_fn")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
Screen* __stdcall Screen_Create(
        int priority, int mode, int first, int second, int third, int fourth) {
    Screen* owner = new Screen;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
