#define data_00491c10 stage_fade_data_00491c10
#define data_0047770c stage_fade_data_0047770c
#define data_00474c40 stage_fade_data_00474c40
#define data_004776e0 stage_fade_data_004776e0
#define data_00477704 stage_fade_data_00477704
#define g_player stage_fade_data_00477834
#define data_00477838 stage_fade_data_00477838
#define data_0047783c stage_fade_data_0047783c
#define data_00476f78 stage_fade_data_00476f78
#define data_00491fc4 stage_fade_data_00491fc4
#define data_00491fb8 stage_fade_data_00491fb8
#define data_00492590 stage_fade_data_00492590
#include "th10/game/native_stage_fade_00404530.hpp"
#include "th10/game/runtime_selector_0043c970.hpp"
extern "C" float data_00476f78;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma code_seg(".text$00404530_fn")
void GameStateFade_00404530::BeginFade() {
    CreateScreenEffect_0043c8b0(15, 2, 30, 0, 0, 0);
    if (!(timer.flags & 1u)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0;
        timer.speed = &data_00476f78;
        timer.flags |= 1u;
    }
    timer.current = 30;
    timer.elapsed = 30.0f;
    timer.previous = 29;
    // Preserve the original order: finish the timer stores before touching
    // the adjacent owner flags word. This intrinsic emits no instructions.
    _ReadWriteBarrier();
    flags |= 2u;
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
