#include <stdint.h>
#include "th10/math/timer.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" double data_00470b70;
extern "C" float data_00470b38;

struct PlayfieldPoint {
    float x;
    float y;
    int32_t OutsidePlayfieldInclusive(float width, float height) const;
};

struct PlayerWrapBounds_00407E40 {
    unsigned char reserved_000[0x30];
    float extent_30;
    float extent_34;
};

struct PlayerWrapVerticalState_00407E40 {
    unsigned char reserved_000[0x39C];
    PlayerWrapBounds_00407E40* bounds_39C;
    unsigned char reserved_3A0[0x14];
    PlayfieldPoint position_3B4;
    unsigned char reserved_3BC[0x80];
    unsigned int flags_43C;
    unsigned char reserved_440[0x18];
    int effect_slot_458;
    unsigned char reserved_45C[0x324];
    FrameTimer wrap_timer_780;

    __declspec(noinline) void WrapVertical();
};

// 0x00407E40. Test the player position against its current bounds, wrap y
// across the playfield edge, advance the wrap timer, queue the wrap effect, and
// toggle the vertical pose bit at a nonpositive timer count. Retail caller
// 0x00406546 supplies the object in EBX; whole-cluster/LTCG work is required
// to connect this ordinary member to that private call edge.
void PlayerWrapVerticalState_00407E40::WrapVertical() {
    if (!position_3B4.OutsidePlayfieldInclusive(
            bounds_39C->extent_34, bounds_39C->extent_30)) {
        return;
    }

    const float y = position_3B4.y;
    bool wrapped = false;
    if (y < data_00470b70) {
        position_3B4.y = bounds_39C->extent_30 + y + data_00470b38;
        wrapped = true;
    } else if (y > data_00470b38) {
        position_3B4.y = y - (bounds_39C->extent_30 + data_00470b38);
        wrapped = true;
    }

    if (wrapped) {
        wrap_timer_780.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            data_00492590.Queue(effect_slot_458, 0);
    }

    if (wrap_timer_780.current <= 0)
        flags_43C ^= 0x00200000u;
}
