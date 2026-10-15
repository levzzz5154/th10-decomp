// 0x0040C9A0: release an enemy's pending drops at a position.
//
// The main item is thrown straight up, the rest are scattered, and the main
// item is cleared. The position arrives in EAX and the drops in EDI; the scatter step
// keeps reading the position from ESI.
#include "th10/game/item_scatter_flush.hpp"
#include "th10/game/player_update_collision.hpp"
#include <string.h>

#pragma code_seg(".text$079h_flush")
void DropSource_0040c9a0::FlushDrops(ItemDrops_0040c9a0* drops) {
    if (drops->main_item > 0)
        data_00477818->Spawn(position, drops->main_item, -1, -1.5707964f, 2.2f);
    ScatterDrops(drops);
    drops->main_item = 0;
}

// 0x0040C9D0: scatter the counted drops around the position.
//
// Each drop lands on an ellipse at a random distance of half to the whole
// radius, and the direction then turns by about a quarter turn. The position
// arrives in ESI and the drops on the stack.
#pragma code_seg(".text$079i_scatter")
void DropSource_0040c9a0::ScatterDrops(ItemDrops_0040c9a0* drops) {
    float angle = Rng_NextFloatSigned(&g_rng) * 3.1415927f;
    for (int kind = 0; kind < 11; ++kind) {
        for (int i = 0; i < drops->counts[kind]; ++i) {
            ScatterOffset_0040c9d0 target;
            target.SetEllipticPolar(angle, drops->spread_x, drops->spread_y);
            // The height is read between the draw and its scaling.
            float roll = (float)ItemScatter_NextU32();
            float height = position[2];
            float distance = roll * (1.0f / 8589934592.0f) + 0.5f;
            target.x *= distance;
            target.y *= distance;
            target.x += position[0];
            target.y += position[1];
            target.z = height;
            data_00477818->Spawn(&target.x, kind + 1, -1, -1.5707964f, 2.2f);
            angle = Angle_Normalize_0044bc70(
                (ItemScatter_NextU32() * (1.0f / 2147483648.0f) - 1.0f) * 0.78539819f
                + angle + 1.5707964f);
        }
    }
    memset(drops->counts, 0, sizeof(drops->counts));
}
#pragma code_seg()
