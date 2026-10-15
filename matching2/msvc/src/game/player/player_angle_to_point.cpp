// 0x00426610: the angle from the player to a point, or the default angle
// when the point is exactly 0,0 away.
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/player_state.hpp"
#pragma intrinsic(atan2)

extern "C" const float data_00470b04, data_00470b94;

#pragma code_seg(".text$f00426610F")
extern "C" __declspec(noinline) double __stdcall Player_AngleToPoint(const Player* player, const Vec3* point) {
    float horizontal = point->x - player->position.x;
    float vertical = point->y - player->position.y;
    if (vertical == data_00470b04 && horizontal == data_00470b04)
        return data_00470b94;
    return atan2(vertical, horizontal);
}
#pragma code_seg()
