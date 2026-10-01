#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00470c68;
extern "C" float data_00470c6c;
extern "C" float data_00476f78;
// 0x004074B0: update the trail velocity through frame16, then toggle bit0.
// Native LTCG retains the player in ESI; SetPolar is the genuine thiscall
// helper at00408750, with a vector in ECX and two float stack arguments.
// The fixed trail decay0.3125 and normal timer increment1 are readonly
// compiler literals bound to their original addresses in the native layout.
#pragma code_seg(".text$01animation")
void PlayerAnimationState_004074B0::AdvanceAnimationFrame() {
    if (animation_timer.current <= 16) {
        const float trail_speed =
            data_00470c68 - animation_timer.elapsed * 0.3125f + speed_3D8;
        velocity.SetPolar(angle_3E4, trail_speed);
    } else {
        flags_43C ^= 1u;
    }

    animation_timer.previous = animation_timer.current;
    if (*animation_timer.speed > data_00470b68 && *animation_timer.speed < data_00470b64) {
        ++animation_timer.current;
        animation_timer.elapsed += 1.0f;
    } else {
        animation_timer.current = int(animation_timer.elapsed += *animation_timer.speed);
    }
}

#pragma code_seg()
