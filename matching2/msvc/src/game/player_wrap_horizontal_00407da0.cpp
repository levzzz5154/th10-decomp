#include <stdint.h>
#include "th10/math/timer.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" float data_00470b40;
extern "C" float data_00470b3c;
extern "C" float data_00470b54;

struct PlayfieldPoint {
    float x;
    float y;
    int32_t OutsidePlayfieldInclusive(float width, float height) const;
};

struct PlayerWrapBounds_00407DA0 {
    unsigned char reserved_000[0x30];
    float extent_30;
    float extent_34;
};

struct PlayerWrapHorizontalState_00407DA0 {
    unsigned char reserved_000[0x39C];
    PlayerWrapBounds_00407DA0* bounds_39C;
    unsigned char reserved_3A0[0x14];
    PlayfieldPoint position_3B4;
    unsigned char reserved_3BC[0x80];
    unsigned int flags_43C;
    unsigned char reserved_440[0x18];
    int effect_slot_458;
    unsigned char reserved_45C[0x2F0];
    FrameTimer wrap_timer_74C;

    __declspec(noinline) void WrapHorizontal();
};

// 0x00407DA0. Test the player position against its current bounds, wrap x
// across the playfield edge, advance the wrap timer, queue the wrap effect, and
// toggle the horizontal pose bit at a nonpositive timer count. Retail caller
// 0x00406533 supplies the object in EBX; whole-cluster/LTCG work is required
// to connect this ordinary member to that private call edge.
void PlayerWrapHorizontalState_00407DA0::WrapHorizontal() {
    if (!position_3B4.OutsidePlayfieldInclusive(
            bounds_39C->extent_34, bounds_39C->extent_30)) {
        return;
    }

    const float x = position_3B4.x;
    bool wrapped = false;
    if (x < data_00470b40) {
        position_3B4.x = bounds_39C->extent_34 + x + data_00470b54;
        wrapped = true;
    } else if (x > data_00470b3c) {
        position_3B4.x = x - (bounds_39C->extent_34 + data_00470b54);
        wrapped = true;
    }

    if (wrapped) {
        wrap_timer_74C.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            data_00492590.Queue(effect_slot_458, 0);
    }

    if (wrap_timer_74C.current <= 0)
        flags_43C ^= 0x00100000u;
}
