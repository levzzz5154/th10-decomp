#pragma once
// Animation-manager lookups as the floating text manager's functions see
// them. Retail has out-of-line copies of each (0x004491C0, 0x004492A0,
// 0x00449450, 0x00449630); the whole-program pass expanded some call sites in
// place, and those call sites use the *Inline spellings here.
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_caller_00419120.hpp"

extern "C" void* data_00491c10;

struct IndicatorAnimationManager_00419120 : RecoveryLookupContext_0040bd80 {
    __forceinline RecoveryIndicatorVm_00419120* FindInline(unsigned int id) {
        if (id == 0)
            return 0;
        RecoveryLookupNode_0040bd80* node;
        for (node = primary; node != 0; node = node->next)
            if (*reinterpret_cast<unsigned int*>(node->object) == id)
                return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
        for (node = secondary; node != 0; node = node->next)
            if (*reinterpret_cast<unsigned int*>(node->object) == id)
                return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
        return 0;
    }

    // Flags a VM and, unless its children were flagged already, each child.
    __forceinline void MarkRemovedInline(unsigned int id) {
        RecoveryIndicatorVm_00419120* vm = FindInline(id);
        if (vm != 0) {
            vm->flags |= 0x04000000u;
            if (!vm->children_flagged)
                for (RecoveryIndicatorVmLink_00419120* child = vm->children;
                     child != 0; child = child->next)
                    child->object->flags |= 0x04000000u;
        }
    }
};

static __forceinline IndicatorAnimationManager_00419120* IndicatorAnimations() {
    return static_cast<IndicatorAnimationManager_00419120*>(data_00491c10);
}

// Removes the handle's VM and forgets it.
static __forceinline void IndicatorHandle_Remove(RecoveryIndicatorHandle_00419120& handle) {
    IndicatorAnimations()->MarkRemovedInline(handle.value);
    handle.value = 0;
}

// The handle's VM; a stale handle is cleared.
static __forceinline RecoveryIndicatorVm_00419120* IndicatorHandle_GetInline(
        RecoveryIndicatorHandle_00419120& handle) {
    RecoveryIndicatorVm_00419120* vm = IndicatorAnimations()->FindInline(handle.value);
    if (vm == 0)
        handle.value = 0;
    return vm;
}

// The same through the out-of-line lookup at 0x004491C0, which takes the
// handle by value.
static inline RecoveryIndicatorVm_00419120* IndicatorHandle_Get(
        RecoveryIndicatorHandle_00419120& handle) {
    RecoveryIndicatorVm_00419120* vm = static_cast<RecoveryIndicatorVm_00419120*>(
        static_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
            static_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
            *reinterpret_cast<RecoveryScriptId_0040bd80*>(&handle)));
    if (vm == 0)
        handle.value = 0;
    return vm;
}
