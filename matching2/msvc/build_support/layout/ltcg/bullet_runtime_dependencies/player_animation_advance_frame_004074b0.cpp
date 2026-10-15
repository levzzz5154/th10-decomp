extern "C" const float flt_0_3125;
#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
extern "C" float flt_1;
extern "C" float flt_1_01;
extern "C" float flt_0_99;
extern "C" float flt_5;
extern "C" const float flt_0_3125;
extern "C" float g_game_speed;
// 0x004074B0. Advance the animation timer and update the player's trail
// velocity while its frame counter is below the trail cutoff.
#pragma code_seg(".text$01aanimation")
void PlayerAnimationState_004074B0::AdvanceAnimationFrame() {
    if (animation_timer.current <= 16) {
        const float trail_speed =
            flt_5 - animation_timer.elapsed * flt_0_3125 + speed_3D8;
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
