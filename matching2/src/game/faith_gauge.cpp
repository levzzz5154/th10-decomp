#include "th10/game/faith_gauge.hpp"

#include <cstring>

extern uint32_t* DAT_0047770c;  // front UI manager (entity block pool)

namespace {

uint32_t ReadU32(const uint8_t* bytes) {
    uint32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteU32(uint8_t* bytes, uint32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

}  // namespace

// 0x00418930 - Add to a faith gauge level. Retail keeps the gauge in
// EAX and the release context in ECX; the resource pointer at +0x9EC8
// travels as a 32-bit word on the host image, so the spawn edge takes
// the truncated token. The boundary test divides the final level and
// the final level minus the added amount by 0x14 (20) with C
// truncation, exactly as retail.
bool FaithGauge_Add(int16_t* level, int16_t amount, void* context,
                    void (*release_anm)(void* context, uint32_t handle),
                    const uint32_t* (*spawn_anm)(uint32_t resource,
                                                 int32_t script,
                                                 int32_t layer)) {
    if (*level > 99) {
        return false;
    }
    const int16_t value = (int16_t)(*level + amount);
    *level = value;
    uint8_t* manager = (uint8_t*)DAT_0047770c;
    if (value > 100) {
        *level = 100;
        if (release_anm != 0) {
            release_anm(context, ReadU32(manager + 0x9E18));
        }
        WriteU32(manager + 0x9E18, 0);
        if (spawn_anm != 0) {
            const uint32_t* handle =
                spawn_anm(ReadU32(manager + 0x9EC8), 0x49, 0xF);
            WriteU32(manager + 0x9E18, *handle);
        }
    }
    return ((int32_t)*level - (int32_t)amount) / 0x14 !=
           (int32_t)*level / 0x14;
}
