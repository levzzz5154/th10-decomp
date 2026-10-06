#include "runtime.hpp"
extern "C" {
extern unsigned short data_00474c48;
__declspec(noinline) int __stdcall StageSchedule_Fire_00427e90(
    PlayerState* player, PickupDescriptor* descriptor, int frame);
}

// Complete real 105-byte schedule walker. Its only native caller is the
// genuine sequence Update body; LTCG derives retail's EDI receiver / EBX frame.
#pragma code_seg(".text$b10dispatch")
int PlayerState::Dispatch(int frame) {
    int rank = data_00474c48 / 20;
    if (rank >= 5) rank = 4;
    if (alternate) rank += 5;
    for (PickupDescriptor* entry = stage_schedule->schedules[rank].entries;
         entry->period >= 0; ++entry) {
        if (frame % entry->period == entry->phase)
            StageSchedule_Fire_00427e90(this, entry, frame);
    }
    return 0;
}
#pragma code_seg()
