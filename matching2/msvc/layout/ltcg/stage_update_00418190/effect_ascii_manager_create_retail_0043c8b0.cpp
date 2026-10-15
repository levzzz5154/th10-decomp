#define data_00491c10 stage_effect_data_00491c10
#define data_0047770c stage_effect_data_0047770c
#define data_00474c40 stage_effect_data_00474c40
#define data_004776e0 stage_effect_data_004776e0
#define data_00477704 stage_effect_data_00477704
#define g_player stage_effect_data_00477834
#define data_00477838 stage_effect_data_00477838
#define data_0047783c stage_effect_data_0047783c
#define data_00476f78 stage_effect_data_00476f78
#define data_00491fc4 stage_effect_data_00491fc4
#define data_00491fb8 stage_effect_data_00491fb8
#define data_00492590 stage_effect_data_00492590
#include "th10/game/runtime_selector_0043c970.hpp"

#pragma code_seg(".text$0043c8b0_fn")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
ScreenEffectController_0043c970* __stdcall CreateScreenEffect_0043c8b0(
        int priority, int mode, int first, int second, int third, int fourth) {
    ScreenEffectController_0043c970* owner = new ScreenEffectController_0043c970;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
