#include "th10/game/enemy_drop_sweep.hpp"


#include <cstring>

namespace {

int32_t ReadI32(const uint8_t* bytes) {
    int32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteI32(uint8_t* bytes, int32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

}  // namespace

// 0x0041BA50 - Sweep the enemy slots for finished pickup effects.
// Retail walks all 0x96 slots in ESI-relative order; both recognized
// kinds (1 and 4) map to drop kind 9, and each hit clears the active
// word before spawning and playing the sound.

uint32_t Enemy_SweepPendingDrops(
        uint8_t* manager,
        void (*spawn_drop)(uint8_t* slot, int32_t kind, int32_t id,
                           float angle, float speed),
        void (*play_drop_sound)()) {
    for (int index = 0; index < 0x96; ++index) {
        uint8_t* slot = manager + 0x3C0 + index * 0x3F0;
        if (ReadI32(slot + 0x30) == 0) {
            continue;
        }
        const int32_t kind = ReadI32(slot + 0x34);
        if (kind != 1 && kind != 4) {
            continue;
        }
        WriteI32(slot + 0x30, 0);
        if (spawn_drop != 0) {
            spawn_drop(slot, 9, -1, -1.5707964f, 2.2f);
        }
        if (play_drop_sound != 0) {
            play_drop_sound();
        }
    }
    return 0;
}
