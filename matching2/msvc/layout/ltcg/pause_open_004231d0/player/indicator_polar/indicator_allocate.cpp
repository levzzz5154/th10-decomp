#include "th10/game/pause_result_open_004231d0/player/indicator_polar/indicator_contract.hpp"

// 00427B50: receiver is the player that owns the pool. The complete real
// caller graph must choose the receiver register; this declaration has no
// unused input. Position and the four scalar values are the five real inputs.
#pragma code_seg(".text$00427b50_fn")
IndicatorSlot* IndicatorPlayerView::AllocateIndicator(
    const PolarVec3* position, float width, float height,
    int frames, unsigned mode) {
    IndicatorSlot* slot = slots;
    for (int index = 0; index < 32; ++index, ++slot) {
        if (slot->flags & 1)
            continue;

        memset(slot, 0, sizeof(*slot));
        slot->flags |= 3;
        memset(&slot->motion, 0, sizeof(slot->motion));
        slot->motion.position = *position;
        slot->width = width;
        slot->height = height;
        slot->timer.Set(frames);
        slot->mode = mode;
        slot->counter = 0;
        slot->limit = 999999;
        slot->phase = 4;
        return slot;
    }
    return slot;
}
#pragma code_seg()
