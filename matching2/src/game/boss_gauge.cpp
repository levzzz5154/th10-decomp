#include "th10/game/boss_gauge.hpp"

#include <cstring>

// Pixel-scale constant applied to grid-cell integers (retail 0x00470B00).
extern float DAT_00470b00;

namespace {

int32_t ReadI32(const uint8_t* bytes) {
    int32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteI32(uint8_t* bytes, int32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

void WriteF32(uint8_t* bytes, float value) {
    memcpy(bytes, &value, sizeof(value));
}

}  // namespace

// 0x00428C20 - Recompute a gauge sprite's position. Retail passes the
// owner in ECX and the sprite in EDX (fastcall). The anchor's cell
// index selects a 0x98-byte row of the owner's grid table; the cell
// integers at +0x3244/+0x3248 are scaled into floats, the flags word is
// cleared, and the anchor-relative offset (anchor position minus sprite
// origin) is added, following the retail store order.
int32_t BossGauge_ComputeSpritePosition(const uint8_t* owner,
                                        GaugeSprite* sprite) {
    const GaugeAnchor* anchor = sprite->anchor;
    const int32_t row = (int32_t)anchor->cell_index * 0x98;
    const float scaled_y = (float)ReadI32(owner + 0x3248 + row) * DAT_00470b00;
    sprite->x = (float)ReadI32(owner + 0x3244 + row) * DAT_00470b00;
    sprite->y = scaled_y;
    sprite->flags = 0;
    sprite->x = (anchor->x - sprite->origin_x) + sprite->x;
    sprite->y = (anchor->y - sprite->origin_y) + sprite->y;
    return 0;
}

// 0x00428E10 - Store a boss's grid cell pair and refresh the derived
// state. Retail carries the boss in EAX and the cell pair as the
// argument; the four gauge channels are 0x98 bytes apart starting at
// +0x332C.
void Boss_SetGridCell(uint8_t* boss, const int32_t cell[2]) {
    WriteI32(boss + 0x3CC, cell[0]);
    WriteI32(boss + 0x3D0, cell[1]);
    WriteF32(boss + 0x3C0, (float)cell[0] * DAT_00470b00);
    WriteF32(boss + 0x3C4, (float)cell[1] * DAT_00470b00);
    WriteI32(boss + 0x332C, 1);
    WriteI32(boss + 0x33C4, 1);
    WriteI32(boss + 0x345C, 1);
    WriteI32(boss + 0x34F4, 1);
}
