#include "../../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller_00419120.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" void* g_ascii_manager;
extern "C" int recovery_indicator_owner;
extern "C" float recovery_indicator_eight_00470bd0;
extern "C" float recovery_indicator_one_00470afc;
extern "C" float recovery_indicator_two_00470b08;
extern "C" float recovery_indicator_fifteen_00470c08;
extern "C" float recovery_indicator_three_halves_00470ca8;
extern "C" float recovery_indicator_half_00470b0c;
extern "C" float recovery_indicator_three_quarters_00470ce4;
extern "C" void __cdecl recovery_indicator_free(void* object);

struct HintThread {
    unsigned char reserved_000[0x899C];
    void* resource;
};
struct HintScalePair {
    float x;
    float y;
};

static inline HintVm* FindIndicatorInline(
        void* manager, unsigned int id) {
    if (id == 0)
        return 0;
    RecoveryLookupContext* context =
        static_cast<RecoveryLookupContext*>(manager);
    for (RecoveryLookupNode* node = context->primary;
         node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<HintVm*>(node->object);
    for (RecoveryLookupNode* node = context->secondary;
         node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<HintVm*>(node->object);
    return 0;
}

#pragma code_seg(".text$00419120_fn")
int HintLink::Drain(
        HintUpdateView* state, int release) {
    HintLink* current = this;
    void* manager = g_sprt_ctrl;
    while (current != 0) {
        HintLink* next = current->next;
        HintEntry* entry = current->object;
        if (entry->owner_tag == 0 ||
            entry->owner_tag == recovery_indicator_owner)
            --entry->countdown;
        if (entry->countdown > 0) {
            current = next;
            continue;
        }

        unsigned int* old_handle = &state->handles[state->slot];
        HintVm* old_vm =
            FindIndicatorInline(manager, *old_handle);
        if (old_vm != 0) {
            old_vm->flags |= 0x04000000u;
            if (!old_vm->children_flagged)
                for (HintVmLink* child = old_vm->children;
                     child != 0; child = child->next)
                    child->object->flags |= 0x04000000u;
        }
        *old_handle = 0;
        entry->position.y += entry->intensity * recovery_indicator_eight_00470bd0;

        HintVm* vm;
        if (entry->intensity <= recovery_indicator_one_00470afc) {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate(
                    static_cast<HintThread*>(g_ascii_manager)->resource,
                    &result, state->slot + 2, &entry->position));
            manager = g_sprt_ctrl;
            unsigned int* handle = &state->handles[state->slot];
            vm = FindIndicatorInline(manager, *handle);
            if (vm == 0)
                *handle = 0;
            vm->font_width = 15;
            vm->font_height = 15;
            HintScalePair source = {
                entry->intensity, entry->intensity
            };
            HintScalePair destination = {
                entry->intensity * recovery_indicator_three_halves_00470ca8, 0.0f
            };
            reinterpret_cast<EntityMovementSlot*>(vm)->Initialise(
                reinterpret_cast<const MovementPair*>(&destination),
                reinterpret_cast<const MovementPair*>(&source), 8, 4);
        } else if (entry->intensity <= recovery_indicator_two_00470b08) {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate(
                    static_cast<HintThread*>(g_ascii_manager)->resource,
                    &result, state->slot + 12, &entry->position));
            unsigned int* handle = &state->handles[state->slot];
            RecoveryScriptId id = { static_cast<int>(*handle) };
            vm = static_cast<HintVm*>(
                reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
                    static_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
            if (vm == 0)
                *handle = 0;
            unsigned char font_size = static_cast<unsigned char>(
                static_cast<int>(entry->intensity * recovery_indicator_fifteen_00470c08));
            vm->font_width = font_size;
            vm->font_height = font_size;
            HintScalePair source = {
                entry->intensity * recovery_indicator_half_00470b0c,
                entry->intensity * recovery_indicator_half_00470b0c
            };
            HintScalePair destination = {
                entry->intensity * recovery_indicator_three_quarters_00470ce4, 0.0f
            };
            reinterpret_cast<EntityMovementSlot*>(vm)->Initialise(
                reinterpret_cast<const MovementPair*>(&destination),
                reinterpret_cast<const MovementPair*>(&source), 8, 4);
            manager = g_sprt_ctrl;
        } else {
            void* result;
            state->handles[state->slot] = reinterpret_cast<unsigned int>(
                *RecoveryPlayerAnimationCreate(
                    static_cast<HintThread*>(g_ascii_manager)->resource,
                    &result, state->slot + 12, &entry->position));
            manager = g_sprt_ctrl;
            unsigned int* handle = &state->handles[state->slot];
            RecoveryScriptId id = { static_cast<int>(*handle) };
            vm = static_cast<HintVm*>(
                reinterpret_cast<RecoveryLookup*>(manager)->Find(
                    static_cast<RecoveryLookupContext*>(manager), id));
            if (vm == 0)
                *handle = 0;
            vm->font_width = 30;
            vm->font_height = 30;
            HintScalePair source = {
                entry->intensity * recovery_indicator_half_00470b0c,
                entry->intensity * recovery_indicator_half_00470b0c
            };
            HintScalePair destination = {
                entry->intensity * recovery_indicator_three_quarters_00470ce4, 0.0f
            };
            reinterpret_cast<EntityMovementSlot*>(vm)->Initialise(
                reinterpret_cast<const MovementPair*>(&destination),
                reinterpret_cast<const MovementPair*>(&source), 8, 4);
        }

        switch (entry->anchor_mode) {
        case 0:
            state->positions[state->slot] = vm->position;
            state->values[state->slot] = entry->offset;
            vm->FormatCentered(manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            manager = g_sprt_ctrl;
            break;
        case 1:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x += entry->offset * recovery_indicator_half_00470b0c;
            state->values[state->slot] = entry->offset;
            reinterpret_cast<RecoveryTextVm*>(vm)->MarkText(
                manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFF7FFFFu) | 0x00040000u;
            manager = g_sprt_ctrl;
            break;
        case 2:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x -= entry->offset * recovery_indicator_half_00470b0c;
            state->values[state->slot] = entry->offset;
            vm->FormatRightAligned(manager, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFFBFFFFu) | 0x00080000u;
            manager = g_sprt_ctrl;
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
            recovery_indicator_free(entry);
            manager = g_sprt_ctrl;
        }
        current = next;
    }
    return 0;
}
#pragma code_seg()
