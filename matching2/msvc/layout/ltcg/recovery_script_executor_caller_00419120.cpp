#include "th10/game/recovery_script_executor_caller_00419120.hpp"

extern "C" void* data_00491c10;
extern "C" void* g_ascii_manager;
extern "C" int recovery_indicator_owner_00474c84;
extern "C" float recovery_indicator_eight_00470bd0;
extern "C" float recovery_indicator_one_00470afc;
extern "C" float recovery_indicator_two_00470b08;
extern "C" float recovery_indicator_fifteen_00470c08;
extern "C" float recovery_indicator_three_halves_00470ca8;
extern "C" float recovery_indicator_half_00470b0c;
extern "C" float recovery_indicator_three_quarters_00470ce4;
extern "C" void __cdecl recovery_indicator_free_004524a1(void* object);

struct RecoveryIndicatorThread_00419120 {
    unsigned char reserved_000[0x899C];
    void* resource;
};
struct RecoveryIndicatorScalePair_00419120 {
    float x;
    float y;
};

static inline RecoveryIndicatorVm_00419120* FindIndicatorInline(
        void* manager, unsigned int id) {
    if (id == 0)
        return 0;
    RecoveryLookupContext_0040bd80* context =
        static_cast<RecoveryLookupContext_0040bd80*>(manager);
    for (RecoveryLookupNode_0040bd80* node = context->primary;
         node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
    for (RecoveryLookupNode_0040bd80* node = context->secondary;
         node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
    return 0;
}

#pragma code_seg(".text$00419120_fn")
int RecoveryIndicatorLink_00419120::Drain(
        RecoveryIndicatorState_00419120* state, int release) {
    RecoveryIndicatorLink_00419120* current = this;
    void* manager = data_00491c10;
    while (current != 0) {
        RecoveryIndicatorLink_00419120* next = current->next;
        RecoveryIndicatorEntry_00419120* entry = current->object;
        if (entry->owner_tag == 0 ||
            entry->owner_tag == recovery_indicator_owner_00474c84)
            --entry->countdown;
        if (entry->countdown > 0) {
            current = next;
            continue;
        }

        unsigned int* old_handle = &state->handles[state->slot];
        RecoveryIndicatorVm_00419120* old_vm =
            FindIndicatorInline(manager, *old_handle);
        if (old_vm != 0) {
            old_vm->flags |= 0x04000000u;
            if (!old_vm->children_flagged)
                for (RecoveryIndicatorVmLink_00419120* child = old_vm->children;
                     child != 0; child = child->next)
                    child->object->flags |= 0x04000000u;
        }
        *old_handle = 0;
        entry->position.y += entry->intensity * recovery_indicator_eight_00470bd0;

        RecoveryIndicatorVm_00419120* vm;
        if (entry->intensity <= recovery_indicator_one_00470afc) {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate_00448db0(
                    static_cast<RecoveryIndicatorThread_00419120*>(g_ascii_manager)->resource,
                    &result, state->slot + 2, &entry->position));
            manager = data_00491c10;
            unsigned int* handle = &state->handles[state->slot];
            vm = FindIndicatorInline(manager, *handle);
            if (vm == 0)
                *handle = 0;
            vm->font_width = 15;
            vm->font_height = 15;
            RecoveryIndicatorScalePair_00419120 source = {
                entry->intensity, entry->intensity
            };
            RecoveryIndicatorScalePair_00419120 destination = {
                entry->intensity * recovery_indicator_three_halves_00470ca8, 0.0f
            };
            reinterpret_cast<EntityMovementSlot_0041ab70*>(vm)->Initialise(
                reinterpret_cast<const MovementPair_0041ab70*>(&destination),
                reinterpret_cast<const MovementPair_0041ab70*>(&source), 8, 4);
        } else if (entry->intensity <= recovery_indicator_two_00470b08) {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate_00448db0(
                    static_cast<RecoveryIndicatorThread_00419120*>(g_ascii_manager)->resource,
                    &result, state->slot + 12, &entry->position));
            unsigned int* handle = &state->handles[state->slot];
            RecoveryScriptId_0040bd80 id = { static_cast<int>(*handle) };
            vm = static_cast<RecoveryIndicatorVm_00419120*>(
                reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
                    static_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
            if (vm == 0)
                *handle = 0;
            unsigned char font_size = static_cast<unsigned char>(
                static_cast<int>(entry->intensity * recovery_indicator_fifteen_00470c08));
            vm->font_width = font_size;
            vm->font_height = font_size;
            RecoveryIndicatorScalePair_00419120 source = {
                entry->intensity * recovery_indicator_half_00470b0c,
                entry->intensity * recovery_indicator_half_00470b0c
            };
            RecoveryIndicatorScalePair_00419120 destination = {
                entry->intensity * recovery_indicator_three_quarters_00470ce4, 0.0f
            };
            reinterpret_cast<EntityMovementSlot_0041ab70*>(vm)->Initialise(
                reinterpret_cast<const MovementPair_0041ab70*>(&destination),
                reinterpret_cast<const MovementPair_0041ab70*>(&source), 8, 4);
            manager = data_00491c10;
        } else {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate_00448db0(
                    static_cast<RecoveryIndicatorThread_00419120*>(g_ascii_manager)->resource,
                    &result, state->slot + 12, &entry->position));
            manager = data_00491c10;
            unsigned int* handle = &state->handles[state->slot];
            RecoveryScriptId_0040bd80 id = { static_cast<int>(*handle) };
            vm = static_cast<RecoveryIndicatorVm_00419120*>(
                reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(
                    static_cast<RecoveryLookupContext_0040bd80*>(manager), id));
            if (vm == 0)
                *handle = 0;
            vm->font_width = 30;
            vm->font_height = 30;
            RecoveryIndicatorScalePair_00419120 source = {
                entry->intensity * recovery_indicator_half_00470b0c,
                entry->intensity * recovery_indicator_half_00470b0c
            };
            RecoveryIndicatorScalePair_00419120 destination = {
                entry->intensity * recovery_indicator_three_quarters_00470ce4, 0.0f
            };
            reinterpret_cast<EntityMovementSlot_0041ab70*>(vm)->Initialise(
                reinterpret_cast<const MovementPair_0041ab70*>(&destination),
                reinterpret_cast<const MovementPair_0041ab70*>(&source), 8, 4);
        }

        switch (entry->anchor_mode) {
        case 0:
            state->positions[state->slot] = vm->position;
            state->values[state->slot] = entry->offset;
            vm->FormatCentered(manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            manager = data_00491c10;
            break;
        case 1:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x += entry->offset * recovery_indicator_half_00470b0c;
            state->values[state->slot] = entry->offset;
            reinterpret_cast<RecoveryTextVm_00447a50*>(vm)->MarkText(
                manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFF7FFFFu) | 0x00040000u;
            manager = data_00491c10;
            break;
        case 2:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x -= entry->offset * recovery_indicator_half_00470b0c;
            state->values[state->slot] = entry->offset;
            vm->FormatRightAligned(manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFFBFFFFu) | 0x00080000u;
            manager = data_00491c10;
            break;
        }

        vm->color.word = entry->color.word;
        vm->color.bytes[3] = 0;
        vm->timestamp = entry->timestamp;
        vm->opacity = entry->color.bytes[3];
        state->slot = (state->slot + 1) % 10;
        if (entry->next != 0)
            entry->next->previous = entry->previous;
        if (entry->previous != 0)
            entry->previous->next = entry->next;
        entry->next = 0;
        entry->previous = 0;
        if (release != 0) {
            recovery_indicator_free_004524a1(entry);
            manager = data_00491c10;
        }
        current = next;
    }
    return 0;
}
#pragma code_seg()
