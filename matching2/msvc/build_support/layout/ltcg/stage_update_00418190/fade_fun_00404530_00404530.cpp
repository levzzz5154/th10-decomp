#define g_sprt_ctrl stage_fade_g_sprt_ctrl
#define g_front stage_fade_g_front
#define data_00474c40 stage_fade_data_00474c40
#define g_ascii_manager stage_fade_data_004776e0
#define g_enemy_ctrl stage_fade_g_enemy_ctrl
#define g_player stage_fade_data_00477834
#define data_00477838 stage_fade_data_00477838
#define data_0047783c stage_fade_data_0047783c
#define data_00476f78 stage_fade_data_00476f78
#define data_00491fc4 stage_fade_data_00491fc4
#define data_00491fb8 stage_fade_data_00491fb8
#define data_00492590 stage_fade_data_00492590
#include "th10/game/background_fade.hpp"
#include "th10/core/screen.hpp"
extern "C" float data_00476f78;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma code_seg(".text$00404530_fn")
void BackGround::BeginFade() {
    Screen_Create(15, 2, 30, 0, 0, 0);
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
