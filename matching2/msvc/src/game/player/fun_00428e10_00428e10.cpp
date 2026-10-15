// 0x00428E10..0x00428E62 (83 bytes): Player::SetFixedPosition.
//
// Moves the player to a fixed-point position (hundredths of a pixel), updates
// the float position to match and flags the four options to jump to their
// places. A replay calls it when a stage starts from a recorded position.
//
// Retail enters this member with the player in EAX and the source in ECX, a
// pair no C++ declaration can name, so the body is compiled in the native-LTCG
// cluster build_support/layout/ltcg/score_gauge_publish_00428e10.json, whose array-walking
// synthetic caller establishes it. The body itself is ordinary C++.
//
// The two words are written through one shared base pointer. Without it the
// backend hoists the first `fild` above the second store and fills the x87
// latency slot with its own schedule, moving 53 of the 83 bytes; with it the
// stores stay adjacent and retail's `mov ecx,1` lands in the `fild`/`fmul`
// slot. The four options are flagged by a loop: the unrolled result is
// retail's four constant-offset stores, while four explicit assignments
// schedule those stores into the x87 latency slots.
#include "th10/game/player.hpp"

#pragma code_seg(".text$01accessor")
Player* Player::SetFixedPosition(const FixedPoint* source) {
    int* fixed = &fixed_position.x;
    fixed[0] = source->x;
    fixed[1] = source->y;
    position.x = (float)fixed_position.x * 0.01f;
    position.y = (float)fixed_position.y * 0.01f;
    for (int i = 0; i < 4; i++) {
        options[i].reset_position = 1;
    }
    return this;
}
#pragma code_seg()
