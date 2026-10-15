#define g_sprt_ctrl stage_timer_g_sprt_ctrl
#define g_front stage_timer_g_front
#define g_globals stage_timer_data_00474c40
#define g_ascii_manager stage_timer_data_004776e0
#define g_enemy_ctrl stage_timer_g_enemy_ctrl
#define g_player stage_timer_data_00477834
#define data_00477838 stage_timer_data_00477838
#define data_0047783c stage_timer_data_0047783c
#define g_game_speed stage_timer_data_00476f78
#define data_00491fc4 stage_timer_data_00491fc4
#define data_00491fb8 stage_timer_data_00491fb8
#define g_sound_manager stage_timer_data_00492590
#include "th10/math/timer.hpp"

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

// 0x00404ED0. The value of += retains the x87 sum for the integer conversion,
// while also storing the binary32 elapsed field.
#pragma code_seg(".text$00404ed0_fn")
void FrameTimer::Tick() {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        ++current;
        elapsed += 1.0f;
    } else {
        current = int(elapsed += *speed);
    }
}

// 0x0044BF40. Converting after the branch reloads the binary32 elapsed field.
#pragma code_seg(".text$0044bf40_fn")
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}

// 0x00428DD0. MSVC emits the retail 32-bit negate before float conversion.
#pragma code_seg(".text$timer_05decrement")
void FrameTimer::Decrement(int count) {
    Advance(float(-count));
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
