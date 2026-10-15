#include "runtime.hpp"
extern "C" {
extern unsigned short data_00474c48;
__declspec(noinline) int __stdcall StageSchedule_Fire_00427e90(
    Player* player, ShotDefinition* shot, int frame);
}

// The complete 105-byte shot walker. Its only native caller is
// UpdateShooting; LTCG derives retail's EDI receiver and EBX frame.
#pragma code_seg(".text$f00428160F")
int Player::FireShots(int frame) {
    int level = data_00474c48 / 20;  // whole units of power
    if (level >= 5) level = 4;
    if (focused) level += 5;
    for (ShotDefinition* shot = shot_type->lists[level].shots; shot->period >= 0; ++shot) {
        if (frame % shot->period == shot->phase)
            StageSchedule_Fire_00427e90(this, shot, frame);
    }
    return 0;
}
#pragma code_seg()
