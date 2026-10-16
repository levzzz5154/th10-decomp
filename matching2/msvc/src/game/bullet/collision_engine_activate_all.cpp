// 0x00408460: start the vanish of every live collision record.
//
// With `idle_only` set, records whose countdown is still running are left
// alone. Retail keeps this out-of-line copy without a remaining caller; the
// engine arrives in EAX and the flag in EBX.
#include "th10/game/player_update_collision.hpp"

#pragma code_seg(".text$069h_all")
void CollisionEngine::ActivateAll(int idle_only) {
    CollisionRecord* record = records;
    int remaining = 2000;
    do {
        if (record->state != 0 && record->state != 3 &&
                (!idle_only || !record->countdown))
            record->Activate();
        ++record;
    } while (--remaining);
}
#pragma code_seg()
