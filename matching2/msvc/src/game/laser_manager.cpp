// 0x0041C800 and 0x0041C850: the player's view of the laser list: test every
// laser against a point, or retire them all.
#include "../../layout/ltcg/player_state_collision_runtime/player_state.hpp"

#pragma code_seg(".text$f0041c800F")
int LaserManager::Evaluate(const Vec3* point, float radius, int mode) {
    Laser* record = first;
    evaluation_point = *point;
    int total = 0;
    while (record) {
        Laser* next = record->next;
        if (record->state != 1) total += record->Evaluate(point, radius, mode);
        record = next;
    }
    return total;
}
#pragma code_seg(".text$f0041c850F")
int LaserManager::Reset(int mode) {
    Laser* record = first;
    while (record) {
        Laser* next = record->next;
        if (record->state != 1) record->Retire(mode);
        record = next;
    }
    return 1;
}
#pragma code_seg()
