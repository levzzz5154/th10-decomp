// 0x00419120 - drains a queue of pending floating texts.
//
// Each ready entry replaces the oldest of the ten sprite slots with a new
// text animation and draws its number into that animation's texture.
// Retail: queue head EAX; manager and release flag on the stack; RET 8.
#include "th10/game/indicator_animation_lookup_00419120.hpp"

extern "C" int recovery_indicator_owner_00474c84;
extern "C" void __cdecl recovery_indicator_free_004524a1(void* object);

struct HintScalePair_00419120 {
    float x;
    float y;
};

struct HintThread_00419120 {
    unsigned char reserved_000[0x899C];
    void* text_animations;    // the loaded text animation file
};
extern "C" HintThread_00419120* g_ascii_manager;

static __forceinline HintHandle_00419120* AsHandle(void** result) {
    return reinterpret_cast<HintHandle_00419120*>(result);
}

static inline void StartScale(HintVm_00419120* vm,
        HintScalePair_00419120* to, HintScalePair_00419120* from) {
    reinterpret_cast<EntityMovementSlot_0041ab70*>(vm)->Initialise(
        reinterpret_cast<const MovementPair_0041ab70*>(to),
        reinterpret_cast<const MovementPair_0041ab70*>(from), 8, 4);
}

#pragma code_seg(".text$00419120_fn")
int HintLink_00419120::Drain(
        HintUpdateView* state, int release) {
    HintLink_00419120* next;
    for (HintLink_00419120* current = this; current != 0; current = next) {
        next = current->next;
        HintEntry_00419120* entry = current->object;
        if (entry->owner_tag == 0 ||
            entry->owner_tag == recovery_indicator_owner_00474c84)
            --entry->countdown;
        if (entry->countdown > 0)
            continue;

        // The text takes over the oldest sprite slot.
        IndicatorHandle_Remove(state->handles[state->slot]);
        entry->position.y += entry->intensity * 8.0f;

        HintVm_00419120* vm;
        if (entry->intensity <= 1.0f) {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate_00448db0(
                animations, &created, state->slot + 2, &entry->position));
            vm = IndicatorHandle_GetInline(state->handles[state->slot]);
            vm->font_width = 15;
            vm->font_height = 15;
            HintScalePair_00419120 from = {
                entry->intensity, entry->intensity
            };
            HintScalePair_00419120 to = {
                entry->intensity * 1.5f, 0.0f
            };
            StartScale(vm, &to, &from);
        } else if (entry->intensity <= 2.0f) {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate_00448db0(
                animations, &created, state->slot + 12, &entry->position));
            vm = IndicatorHandle_Get(state->handles[state->slot]);
            vm->font_width = static_cast<unsigned char>(entry->intensity * 15.0f);
            vm->font_height = vm->font_width;
            HintScalePair_00419120 to = {
                entry->intensity * 0.75f, 0.0f
            };
            HintScalePair_00419120 from = {
                entry->intensity * 0.5f, entry->intensity * 0.5f
            };
            StartScale(vm, &to, &from);
        } else {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate_00448db0(
                animations, &created, state->slot + 12, &entry->position));
            vm = IndicatorHandle_Get(state->handles[state->slot]);
            vm->font_width = 30;
            vm->font_height = 30;
            HintScalePair_00419120 to = {
                entry->intensity * 0.75f, 0.0f
            };
            HintScalePair_00419120 from = {
                entry->intensity * 0.5f, entry->intensity * 0.5f
            };
            StartScale(vm, &to, &from);
        }

        switch (entry->anchor_mode) {
        case 0:
            state->positions[state->slot] = vm->position;
            state->widths[state->slot] = entry->offset;
            vm->FormatCentered(data_00491c10, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            break;
        case 1:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x += entry->offset * 0.5f;
            state->widths[state->slot] = entry->offset;
            reinterpret_cast<RecoveryTextVm_00447a50*>(vm)->MarkText(
                data_00491c10, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFF7FFFFu) | 0x00040000u;
            break;
        case 2:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x -= entry->offset * 0.5f;
            state->widths[state->slot] = entry->offset;
            vm->FormatRightAligned(data_00491c10, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFFBFFFFu) | 0x00080000u;
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
        if (release != 0)
            recovery_indicator_free_004524a1(entry);
    }
    return 0;
}
#pragma code_seg()
