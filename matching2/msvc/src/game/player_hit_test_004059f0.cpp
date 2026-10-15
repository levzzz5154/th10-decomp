// 0x004059F0: test a point against the bomb's area.
#include "../../layout/ltcg/player_state_collision_runtime/runtime.hpp"

#pragma code_seg(".text$f004059f0F")
int PickupPlayer::HitTest(const PickupPoint* point) {
    if (active == 0) return 0;
    int result = 0;
    float dy = point->y - position.y;
    float dx = point->x - position.x;
    if (dx*dx + dy*dy < radius*radius) {
        if (mode == 0 && (data_004776f4->flags & 1)) result = 3;
        else if (data_004776f4->flags & 1) result = 38;
        else result = data_00477704->alternate_mode ? 38 : 5;
    } else {
        if (data_004776f4->flags & 1) {
            if (mode == 1) result = data_00474c68 ? 23 : 26;
        } else if (data_00477704->alternate_mode != 0 && mode == 0) {
            result = data_00474c68 == 0 ? 20 : 16;
        }
    }
    return result;
}
#pragma code_seg()
