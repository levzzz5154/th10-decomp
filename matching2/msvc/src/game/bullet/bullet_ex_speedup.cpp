// 0x004074B0: BulletExSpeedup::StepSpeedup — enemy-bullet Ex-transform
// speedup burst (flags +0x43C bit 0): decelerates from +5.0f down to speed_3D8
// over 16 frames, then clears bit 0. Native LTCG retains the bullet in ESI;
// SetPolar is the genuine thiscall helper at 0x00408750.
#include "th10/game/bullet_ex_motion.hpp"
extern "C" float flt_1;
extern "C" float flt_1_01;
extern "C" float flt_0_99;
extern "C" float flt_5;
extern "C" float flt_0_3125;
extern "C" float g_game_speed;
#pragma code_seg(".text$01animation")
void BulletExSpeedup::StepSpeedup() {
    if (animation_timer.current <= 16) {
        const float trail_speed =
            flt_5 - animation_timer.elapsed * 0.3125f + speed_3D8;
        velocity.SetPolar(angle_3E4, trail_speed);
    } else {
        flags_43C ^= 1u;
    }

    animation_timer.previous = animation_timer.current;
    if (*animation_timer.speed > flt_0_99 && *animation_timer.speed < flt_1_01) {
        ++animation_timer.current;
        animation_timer.elapsed += 1.0f;
    } else {
        animation_timer.current = int(animation_timer.elapsed += *animation_timer.speed);
    }
}

#pragma code_seg()
