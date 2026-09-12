#include "th10/game/effect_indicator_queue.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/game/stage_focus_fade.hpp"
#include "th10/game/stage_tips.hpp"
#include "th10/runtime/missing_edge.hpp"



#include <new>

#include <cstring>

// Stage-tip manager global declared in retail at 0x00477814.
StageTipManager* DAT_00477814;

// Difficulty globals shared with the tip-creation path.
extern int32_t DAT_00474c7c;  // difficulty setting
extern int32_t DAT_00474c84;  // tip display mode
extern int32_t DAT_00474c88;  // display value used while mode == 0
extern int32_t DAT_00474c8c;  // display value used while mode != 0
extern uint32_t DAT_00491be4;
extern uint8_t DAT_00491d6a;
// Player block published at retail 0x00477834; the focus-fade update reads
// the position floats at +0x3C0/+0x3C4 as the camera anchor. The standalone
// host never publishes the block, so the host path treats it as optional.
extern uint32_t* DAT_00477834;

namespace {
StageTipRuntimeBindings g_stage_tip_bindings = {};

// 0x00419650 - The stage-tip update edge doubles as the stage-focus fade
// driver. The retail body resets the secondary counter when the display
// mode (dword_474C84) differs from the manager's +0xD8 snapshot, expires
// the current difficulty's queued chain through 0x00419120, then walks ten
// focus slots scattered through the manager tail (+0xDC handles, +0x104
// x/y/z triples, +0x17C half-widths), resolving each handle through the
// animation manager's world/UI lists (dword_491C10 + 0x72DAD4 / +0x72DADC)
// and fading the matched entity's alpha around the player camera.
// Copy one retail focus slot (scattered manager tail fields) into the
// compact StageFocusSlot layout the recovery consumes.
static void FocusSlotLoad(StageFocusSlot* slot, const unsigned char* bytes,
                          int index) {
    slot->handle = *(const uint32_t*)(bytes + 0xDC + 4 * index);
    slot->x = *(const float*)(bytes + 0x104 + 12 * index);
    slot->y = *(const float*)(bytes + 0x108 + 12 * index);
    slot->z = *(const float*)(bytes + 0x10C + 12 * index);
    slot->half_width = *(const float*)(bytes + 0x17C + 4 * index);
}

// Write the recovery's slot back into the manager's retail field layout.
static void FocusSlotStore(const StageFocusSlot* slot, unsigned char* bytes,
                           int index) {
    *(uint32_t*)(bytes + 0xDC + 4 * index) = slot->handle;
    *(float*)(bytes + 0x104 + 12 * index) = slot->x;
    *(float*)(bytes + 0x108 + 12 * index) = slot->y;
    *(float*)(bytes + 0x10C + 12 * index) = slot->z;
    *(float*)(bytes + 0x17C + 4 * index) = slot->half_width;
}

int __fastcall StageTipRuntime_Update(void* owner) {
    // Host path: drive the recovered StageFocus_UpdateFade over the
    // manager's retail focus-slot fields. The retail reads the player
    // position at DAT_00477834 +0x3C0/+0x3C4 and the recovery adds the
    // +224/+16 camera offsets internally, so the env carries the raw
    // floats; the standalone host never publishes the player block, so a
    // missing block reads as the origin.
    unsigned char* bytes = reinterpret_cast<unsigned char*>(owner);
    StageFocusState state;
    state.frame = *(const uint32_t*)(bytes + 0x10);
    state.secondary_frame = *(const uint32_t*)(bytes + 0x14);
    state.stage_id = *(const int32_t*)(bytes + 0xD8);
    // Retail keeps the manager self-pointer at +0x0C (set by 0x00418D40);
    // the recovery only forwards it to the (unwired) prepare callback.
    state.selected = owner;
    for (int index = 0; index < 10; ++index) {
        FocusSlotLoad(&state.slots[index], bytes, index);
    }

    StageFocusEnv env;
    env.current_stage_id = DAT_00474c84;  // retail dword_474C84 comparison
    const unsigned char* player =
        reinterpret_cast<const unsigned char*>(DAT_00477834);
    env.camera_x = player != 0 ? *(const float*)(player + 0x3C0) : 0.0f;
    env.camera_y = player != 0 ? *(const float*)(player + 0x3C4) : 0.0f;
    // Retail resolves each slot handle through the animation manager's
    // world/UI lists (dword_491C10 + 0x72DAD4 / +0x72DADC); the env has no
    // name-list lookup, so empty lists reproduce retail's not-found path,
    // which clears the slot handle. Retail's 0x00419120 chain-head expiry
    // (env.prepare) is not recovered - TODO.
    env.active = 0;
    env.pending = 0;
    env.prepare = 0;

    int result = StageFocus_UpdateFade(&state, &env);

    // The manager is the persistent store: write back the counters and the
    // ten slots (the recovery clears handles whose entity is not found).
    *(uint32_t*)(bytes + 0x10) = state.frame;
    *(uint32_t*)(bytes + 0x14) = state.secondary_frame;
    *(int32_t*)(bytes + 0xD8) = state.stage_id;
    for (int index = 0; index < 10; ++index) {
        FocusSlotStore(&state.slots[index], bytes, index);
    }
    return result;
}

// Retail 0x004198B0: the stage-tip render edge.  The entire body is
// `mov eax, 1; retn` - the listing shows no other effect.
int __fastcall StageTipRuntime_Render(void* owner) {
    (void)owner;
    return 1;
}

void StageTipRuntime_SpawnTip(void* owner, uint32_t text_address,
                              int32_t slot) {
    // Host path: retail 0x0041A120 is the record allocation + chain
    // append modelled by StageTip_Create below (the same body, with the
    // allocator injected); the wrapper's position argument is not
    // carried by the host call sites, so the record spawns at 0 and the
    // slot selects nothing on this path (the built-in tips rely on the
    // display-mode globals StageTip_Create already reads).
    (void)slot;
    static const float origin[3] = {0.0f, 0.0f, 0.0f};
    StageTip_Create((StageTipManager*)owner, origin,
                    (const char*)(uintptr_t)text_address,
                    +[](uint32_t size) { return ::operator new(size); });
}
}  // namespace

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

void StageTipRuntime_SetBindings(const StageTipRuntimeBindings* bindings) {
    if (bindings != 0)
        g_stage_tip_bindings = *bindings;
    else
        memset(&g_stage_tip_bindings, 0, sizeof(g_stage_tip_bindings));
}

// 0x00418E30 - Register the manager's update/render pair, clear its counter,
// and create the two built-in tips when the retail tips option is enabled.

int StageTipRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    SchedulerCallback* update =
        SchedulerCallback_Create(StageTipRuntime_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = state;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* render =
        SchedulerCallback_Create(StageTipRuntime_Render);
    if (render == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    render->flags &= ~2u;
    render->owner = state;
    Scheduler_RegisterSecondary(render, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = render;
    *(uint32_t*)(bytes + 0x10) = 0;

    // Retail gates the two startup tips on the display flag only; the spawn
    // edge itself is mandatory, so a missing binding is a build error rather
    // than a silently skipped pair.
    if (DAT_00491d6a != 0) {
        StageTipRuntime_SpawnTip(state, 0x0046D6D8u, 0);
        StageTipRuntime_SpawnTip(state, 0x0046D6C4u, 1);
    }
    return 0;
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
    // Retail allocates the 0x88-byte record; the host struct carries
    // host-side tail members, so the allocation must match sizeof.
    StageTip* tip = allocate != 0 ? (StageTip*)allocate(sizeof(StageTip)) : 0;
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
