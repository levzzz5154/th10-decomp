// Readable reconstruction of the progress-record leaf pair over the
// persistent block at DAT_0047783c. Run startup sets the record flag byte for
// the active shot type; the main-menu gate disables its stage-practice item
// while no record exists, and the hidden key sequence inside the practice
// menu invokes the unlock-all leaf.
#include "th10/game/progress.hpp"

// MSVC 7.1 is pre-C++11 — use manual typedefs instead of <cstdint>
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

// 0x0042C850 - Return 1 when any of the six main shot-type record flags at
// +0x1D888..+0x1D88D is set, 0 when every byte is clear.
int GameProgress_HasAnyPlayRecord(const void* progress) {
    const uint8_t* bytes = (const uint8_t*)progress;
    for (int index = 0; index < 6; ++index)
        if (bytes[0x1D888 + index] != 0)
            return 1;
    return 0;
}

// 0x0042C8C0 - Set all sixteen shot-type record flags at +0x1D882 and mark
// the first six 8-byte stage records in every per-shot-type table. Retail
// repeats the six stage stores four times per table; the dead passes are
// preserved for faithfulness.
void GameProgress_UnlockAllStages(void* progress) {
    uint8_t* bytes = (uint8_t*)progress;
    for (int index = 0; index < 4; ++index)
        *(uint32_t*)(bytes + 0x1D882 + index * 4) = 0x01010101u;
    for (int table = 0; table < 6; ++table) {
        uint8_t* stages = bytes + 0x4E9 + table * 0x437C;
        for (int pass = 0; pass < 4; ++pass)
            for (int stage = 0; stage < 6; ++stage)
                stages[stage * 8] = 1;
    }
}
