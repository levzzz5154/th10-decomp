#include "th10/game/stage_tips.hpp"

#ifndef _MSC_VER
#include <cstring>
#else
extern "C" void* memset(void*, int, unsigned long);
#endif

// Stage-tip manager global declared in retail at 0x00477814.
StageTipManager* DAT_00477814;

// Difficulty globals shared with the tip-creation path.
extern int32_t DAT_00474c7c;  // difficulty setting
extern int32_t DAT_00474c84;  // tip display mode
extern int32_t DAT_00474c88;  // display value used while mode == 0
extern int32_t DAT_00474c8c;  // display value used while mode != 0

// strncpy with the exact retail semantics (copy up to ``limit`` bytes,
// zero-fill the remainder, no forced terminator), written out so the
// host build does not depend on the CRT's truncation diagnostics.
static void CopyTipText(char* destination, const char* source,
                        unsigned int limit) {
    unsigned int index = 0;
    for (; index < limit && source[index] != 0; ++index) {
        destination[index] = source[index];
    }
    for (; index < limit; ++index) {
        destination[index] = 0;
    }
}

// 0x00418D40 - Construct the 0x1A8-byte stage-tip manager: clear the
// whole state, set constructed bit 1 in the flags word, point all
// sixteen intrusive list sentinels back at the manager with empty
// next/previous links, and publish the instance through the retail
// global at 0x00477814.
StageTipManager* StageTipManager_Construct(StageTipManager* state) {
    memset(state, 0, sizeof(*state));
    state->flags |= 2u;
    for (int index = 0; index < 16; ++index) {
        state->lists[index].owner = (StageTip*)state;
        state->lists[index].next = 0;
        state->lists[index].previous = 0;
    }
    DAT_00477814 = state;
    return state;
}

// 0x0041A120 - Allocate one 0x88-byte stage-tip record, run the same
// initialization as StageTip_Initialize (0x00418D00), append the tip to
// the tail of the current difficulty's chain, and fill in position,
// text, and the display fields selected by the difficulty globals.
//
// Retail ABI: the record's position vector arrives in EBX and the
// allocation goes through the statically linked operator new; the
// readable signature reifies the position and injects the allocator.
// Retail addresses the list head as manager + (DAT_00474C7C * 3 + 0x1E)
// 32-bit words, i.e. sentinel 8 + difficulty of the manager's sixteen
// list heads (+0x78 onward).
//
// Retail never observes an allocation failure (its statically linked
// allocator aborts), so the readable form returns null early instead of
// linking a null record.
StageTip* StageTip_Create(StageTipManager* manager, const float position[3],
                          const char* text, void* (*allocate)(uint32_t)) {
    StageTip* tip = allocate != 0 ? (StageTip*)allocate(0x88) : 0;
    if (tip == 0) {
        return 0;
    }

    // Inlined retail body of StageTip_Initialize (0x00418D00).
    memset(tip, 0, sizeof(StageTip));
    tip->node.next = 0;
    tip->node.previous = 0;
    tip->node.owner = tip;
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;

    // Walk to the tail of the current difficulty's chain and append.
    StageTipNode* tail = &manager->lists[8 + DAT_00474c7c];
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = &tip->node;
    tip->node.previous = tail;

    tip->selection = 0x1E;
    tip->x = position[0];
    tip->y = position[1];
    tip->z = position[2];
    CopyTipText(tip->name, text, 0x40);
    tip->display_zero = 0;
    tip->display_mode = DAT_00474c84;
    tip->display_value = DAT_00474c84 == 0 ? DAT_00474c88 : DAT_00474c8c;
    return tip;
}

// 0x00424650 - Age every selected tip in the current difficulty chain, create
// a replacement through the common 0x0041A120 path, shorten its lifetime by
// sixty frames with a one-frame floor, and install the highlighted style.
StageTip* StageTip_CreateUrgent(StageTipManager* manager,
                                const float position[3], const char* text,
                                void* (*allocate)(uint32_t)) {
    StageTipNode* node = manager->lists[8 + DAT_00474c7c].next;
    while (node != 0) {
        if (node->owner->selection > 0) {
            --node->owner->selection;
        }
        node = node->next;
    }

    StageTip* tip = StageTip_Create(manager, position, text, allocate);
    if (tip == 0) {
        return 0;
    }
    tip->duration -= 60;
    if (tip->duration < 1) {
        tip->duration = 1;
    }
    tip->display_mode = 90;
    tip->state = static_cast<int32_t>(0xffff8080u);
    tip->selection = 30;
    return tip;
}
