#include "th10/game/pool_constructors.hpp"
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstring>

// Retail globals that publish the constructed managers.
uint32_t* DAT_00477840;  // effect manager instance
uint32_t* DAT_0047784c;  // progress manager instance
uint32_t* DAT_0047770c;  // entity block pool instance
extern uint32_t DAT_00491be4;
extern void* g_pGameThread;
extern void __fastcall Entity_Init(void* unused, Entity* entity);
extern "C" void _free(void* memory);

namespace {
EffectManagerRuntimeBindings g_effect_runtime_bindings = {};

int __fastcall EffectRuntime_Update(void* owner) {
    if (g_effect_runtime_bindings.update == 0)
        Runtime_MissingEdge(0x0042B9A0u, "effect bookkeeping update");
    return g_effect_runtime_bindings.update(owner);
}

int __fastcall EffectRuntime_Render(void* owner) {
    if (g_effect_runtime_bindings.render == 0)
        Runtime_MissingEdge(0x0042B9B0u, "effect bookkeeping render");
    return g_effect_runtime_bindings.render(owner);
}

void EffectRuntime_Preload(int frame_stamp, int argument) {
    if (g_effect_runtime_bindings.preload == 0)
        Runtime_MissingEdge(0x0043E5A0u, "effect resource preload");
    g_effect_runtime_bindings.preload(frame_stamp, argument);
}
}  // namespace

// All three retail constructors share the same shape: a prologue of
// per-slot stores (sentinel bit clears, per-channel defaults, vtable
// pointers), followed by a full zero wipe of the whole block that makes
// every prologue store dead, then the constructed bit and the global
// publish. The readable forms keep only the observable effects and
// document the dead prologue.

// 0x0042B430 - Reset the effect manager. The retail prologue clears the
// in-use bit of nine embedded timer sentinels, wipes one 0x3AC-byte
// scratch record at +0x18 (with a 0xFFFF terminator half-word), and
// clears the in-use bit of 0x2D3 0x40-byte slots at +0x3F0 -- all dead
// stores, because the function then zeroes all 0x2E21 words. Bit 1 of
// the leading flags word marks the manager constructed and the instance
// is published through 0x00477840.
void EffectManager_ResetAndPublish(uint32_t* state) {
    memset(state, 0, kEffectManagerDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_00477840 = state;
}

void EffectManagerRuntime_SetBindings(
        const EffectManagerRuntimeBindings* bindings) {
    if (bindings != 0)
        g_effect_runtime_bindings = *bindings;
    else
        memset(&g_effect_runtime_bindings, 0,
               sizeof(g_effect_runtime_bindings));
}

// 0x0042B4D0 - Stamp the manager, install its callback pair, initialize the
// embedded entity/timer record, and preload effect bank 0xC4.
int EffectManagerRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    const int stamp = g_pGameThread != 0
        ? *(int*)((unsigned char*)g_pGameThread + 0x8994) : 0;
    *(int*)(bytes + 0x10) = stamp;

    SchedulerCallback* update =
        SchedulerCallback_Create(EffectRuntime_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = state;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* render =
        SchedulerCallback_Create(EffectRuntime_Render);
    if (render == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    render->flags &= ~2u;
    render->owner = state;
    Scheduler_RegisterSecondary(render, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = render;
    Entity_Init(0, (Entity*)(bytes + 0x18));
    *(int*)(bytes + 0x320) = stamp;
    // Retail's tail call is unconditional; the edge is mandatory so a
    // missing binding fails loudly instead of skipping the preload.
    EffectRuntime_Preload(stamp, 0xC4);
    return 0;
}

void EffectManagerRuntime_Destroy(void* state) {
    if (state == 0)
        return;
    unsigned char* bytes = (unsigned char*)state;
    SchedulerCallback** update = (SchedulerCallback**)(bytes + 8);
    SchedulerCallback** render = (SchedulerCallback**)(bytes + 12);
    if (DAT_00491be4 != 0) {
        if (*update != 0)
            Scheduler_Remove(*update, (void*)(uintptr_t)DAT_00491be4);
        if (*render != 0)
            Scheduler_Remove(*render, (void*)(uintptr_t)DAT_00491be4);
    }
    *update = 0;
    *render = 0;
    DAT_00477840 = 0;
    void** buffer = (void**)(bytes + 0x370);
    if (*buffer != 0)
        _free(*buffer);
    *buffer = 0;
}

// 0x0042C920 - Construct the progress manager. The retail prologue
// installs two vtable pointers and seeds four gauge channels with the
// {enabled = 1, limit = 999} defaults before the full 0x16B3-word wipe
// discards them. Bit 1 of the flags word at +0x04 marks the manager
// constructed and the instance is published through 0x0047784C.
uint32_t* ProgressManager_ConstructAndPublish(uint32_t* state) {
    memset(state, 0, kProgressManagerDwords * sizeof(uint32_t));
    state[1] |= 2u;
    DAT_0047784c = state;
    return state;
}

// 0x00413810 - Construct the entity block pool. Retail runs
// _eh_vector_constructor_iterator_ over six embedded arrays of
// 0x3AC-byte entities (10, 10, 9, 4, 2, and 7 elements at word offsets
// 4, 0x932, 0x1260, 0x1AA3, 0x1E4F, and 0x2025), then performs the same
// clear-and-publish tail as the other pool constructors: the sentinel
// bit clears and the 0x3AC-byte scratch wipe at +0x9A48 are dead
// because the whole 0x27B4-word block is zeroed afterwards. Bit 1 of
// the leading flags word marks the pool constructed and the instance is
// published through 0x0047770C.
uint32_t* EntityBlockPool_ConstructAndPublish(
        uint32_t* state, void (*construct_entity)(void*)) {
    static const struct {
        uint32_t word_offset;
        uint32_t count;
    } kArrays[6] = {
        {0x0004, 10}, {0x0932, 10}, {0x1260, 9},
        {0x1AA3, 4},  {0x1E4F, 2},  {0x2025, 7},
    };
    const uint32_t kEntityDwords = 0x3AC / 4;
    if (construct_entity != 0) {
        for (int range = 0; range < 6; ++range) {
            for (uint32_t index = 0; index < kArrays[range].count; ++index) {
                construct_entity(state + kArrays[range].word_offset +
                                 index * kEntityDwords);
            }
        }
    }
    memset(state, 0, kEntityBlockPoolDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_0047770c = state;
    return state;
}
