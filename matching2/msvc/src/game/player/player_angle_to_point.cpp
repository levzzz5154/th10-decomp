// 0x00426610: the angle from the player to a point, or the default angle
// when the point is exactly 0,0 away.
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/player_state.hpp"
#pragma intrinsic(atan2)

extern "C" const float flt_0, flt_pi_2;

#pragma code_seg(".text$f00426610F")
extern "C" __declspec(noinline) double __stdcall Player_AngleToPoint(const Player* player, const Vec3* point) {
    float horizontal = point->x - player->position.x;
    float vertical = point->y - player->position.y;
    if (vertical == flt_0 && horizontal == flt_0)
        return flt_pi_2;
    return atan2(vertical, horizontal);
}
#pragma code_seg()
