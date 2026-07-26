// =============================================================================
// stage_slot_state.cpp - Per-stage slot state construction
// Functions: 0x00415B00
// =============================================================================
#include "th10/game/stage_slot_state.hpp"

#include <cstring>

#include "th10/game/entity_region_sweep.hpp"

namespace {

// Retail immediates: 0x41000000 and 0x41C80000 as floats, and two packed RGB
// constants stored as raw dwords.
const float kRadius = 8.0f;
const float kRegionExtent = 25.0f;
const unsigned int kColorA = 0x00F8F08Fu;
const unsigned int kColorB = 0x008088FFu;

// Both VMs are built by the same sequence: allocate, force the flag into the
// control word, select script 15, bind the script, then register and keep the
// returned handle.
int CreateSparkleVm(const StageSlotInitHooks* hooks, void* archive, int index) {
    unsigned int* vm = hooks->allocate_vm(hooks->game_state);
    vm[215] |= (unsigned int)STAGE_SLOT_VM_FLAG;
    vm[8] = STAGE_SLOT_VM_SCRIPT;
    hooks->init_script(archive, vm, index);
    return hooks->register_vm(hooks->game_state, vm);
}

// Retail resolves the handle, clears the stored handle when the lookup fails,
// and then writes through the returned pointer regardless. The clear is kept
// because it is observable; the unconditional write is discussed below.
void StampRecord(const StageSlotInitHooks* hooks, int* handle_slot, int field) {
    unsigned char* record = hooks->find_vm(hooks->game_state, *handle_slot);
    if (record == 0) {
        *handle_slot = 0;
        return;
    }
    record[field] = (unsigned char)STAGE_SLOT_RECORD_VALUE;
}

} // namespace

// 0x00415B00 - Initialize one stage slot in place.
//
// The caller allocates 0x90 bytes and hands them straight here. The function
// clears bit 0 of the three timer flag words before memsetting the whole
// block, so those three clears are dead; they are preserved because they are
// part of the observed instruction sequence, and because the memset then
// guarantees every subsequent "is bit 0 clear" test takes its initializing
// branch. Each of the three timers therefore reduces exactly to the shared
// Timer_Reset leaf, which this function reuses rather than restating.
//
// After the timers it publishes the definition pointer, builds two sparkle
// VMs from the archive carried by the resource object, and stamps two byte
// fields on each resolved record. Retail null-checks each lookup, zeroes the
// stored handle on failure, and then writes through the pointer anyway; that
// final write is a genuine null dereference on the failure path. It is not
// reproduced literally here because doing so would be undefined behavior in
// C++ rather than a faithful fault, so the handle clear is kept and the write
// is skipped. This is the one place where this reconstruction deliberately
// diverges from the retail instruction stream.
//
// The tail sweeps the same 2000-entry pool the region sweep at 0x00408210
// walks, using the identical stride and the identical "state is 0 or 3" skip,
// then drains the teardown list and flushes the message host.
StageSlotState* StageSlotState_Init(StageSlotState* slot,
                                    const void* definition,
                                    const StageSlotInitHooks* hooks) {
    // Dead: the memset below clears these same bits.
    slot->timer_a.flags &= ~1u;
    slot->timer_b.flags &= ~1u;
    slot->timer_c.flags &= ~1u;
    std::memset(slot, 0, sizeof(StageSlotState));

    Timer_Reset(&slot->timer_a);
    Timer_Reset(&slot->timer_b);
    slot->field_58 = 0;
    Timer_Reset(&slot->timer_c);

    slot->definition = definition;

    void* archive = hooks->resource_object[STAGE_SLOT_ARCHIVE_INDEX];
    slot->vm_handle_a = CreateSparkleVm(hooks, archive, 0);
    slot->vm_handle_b = CreateSparkleVm(hooks, archive, 1);

    StampRecord(hooks, &slot->vm_handle_a, STAGE_SLOT_RECORD_FIELD_A);
    StampRecord(hooks, &slot->vm_handle_a, STAGE_SLOT_RECORD_FIELD_B);
    StampRecord(hooks, &slot->vm_handle_b, STAGE_SLOT_RECORD_FIELD_A);
    StampRecord(hooks, &slot->vm_handle_b, STAGE_SLOT_RECORD_FIELD_B);

    slot->radius = kRadius;
    slot->reserved_64[0] = 0;
    slot->reserved_64[1] = 0;
    slot->region[0] = kRegionExtent;
    slot->region[1] = 0.0f;
    slot->region[2] = 0.0f;
    slot->field_80 = 0;
    slot->field_84 = 0;
    slot->color_a = kColorA;
    slot->color_b = kColorB;

    unsigned char* entry = hooks->pool_object + 96;
    for (int remaining = ENTITY_REGION_SWEEP_COUNT; remaining != 0;
         --remaining, entry += ENTITY_REGION_SWEEP_STRIDE) {
        const short state =
            *(const short*)(entry + ENTITY_REGION_ENTRY_STATE);
        if (state != 0 && state != 3)
            hooks->activate_entry(hooks->context, slot->region, entry);
    }

    for (StageEffectNode* node = hooks->effect_list; node != 0;) {
        StageEffectNode* next = node->next;
        if (node->kind != 1) hooks->release_effect(node);
        node = next;
    }

    hooks->flush_message_host(hooks->context);
    return slot;
}
