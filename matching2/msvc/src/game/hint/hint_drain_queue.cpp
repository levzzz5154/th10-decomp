// 0x00419120 - drains a queue of pending floating texts.
//
// Each ready entry replaces the oldest of the ten sprite slots with a new
// text animation and draws its number into that animation's texture.
// Retail: queue head EAX; manager and release flag on the stack; RET 8.
#include "th10/game/indicator_animation_lookup.hpp"

extern "C" int recovery_indicator_owner;
extern "C" void __cdecl recovery_indicator_free(void* object);

struct HintScalePair {
    float x;
    float y;
};

struct HintThread {
    unsigned char reserved_000[0x899C];
    void* text_animations;    // the loaded text animation file
};
extern "C" HintThread* g_ascii_manager;

static __forceinline HintHandle* AsHandle(void** result) {
    return reinterpret_cast<HintHandle*>(result);
}

static inline void StartScale(HintVm* vm,
        HintScalePair* to, HintScalePair* from) {
    reinterpret_cast<EntityMovementSlot*>(vm)->Initialise(
        reinterpret_cast<const MovementPair*>(to),
        reinterpret_cast<const MovementPair*>(from), 8, 4);
}

#pragma code_seg(".text$00419120_fn")
int HintLink::Drain(
        HintUpdateView* state, int release) {
    HintLink* next;
    for (HintLink* current = this; current != 0; current = next) {
        next = current->next;
        HintEntry* entry = current->object;
        if (entry->owner_tag == 0 ||
            entry->owner_tag == recovery_indicator_owner)
            --entry->countdown;
        if (entry->countdown > 0)
            continue;

        // The text takes over the oldest sprite slot.
        IndicatorHandle_Remove(state->handles[state->slot]);
        entry->position.y += entry->intensity * 8.0f;

        HintVm* vm;
        if (entry->intensity <= 1.0f) {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate(
                animations, &created, state->slot + 2, &entry->position));
            vm = IndicatorHandle_GetInline(state->handles[state->slot]);
            vm->font_width = 15;
            vm->font_height = 15;
            HintScalePair from = {
                entry->intensity, entry->intensity
            };
            HintScalePair to = {
                entry->intensity * 1.5f, 0.0f
            };
            StartScale(vm, &to, &from);
        } else if (entry->intensity <= 2.0f) {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate(
                animations, &created, state->slot + 12, &entry->position));
            vm = IndicatorHandle_Get(state->handles[state->slot]);
            vm->font_width = static_cast<unsigned char>(entry->intensity * 15.0f);
            vm->font_height = vm->font_width;
            HintScalePair to = {
                entry->intensity * 0.75f, 0.0f
            };
            HintScalePair from = {
                entry->intensity * 0.5f, entry->intensity * 0.5f
            };
            StartScale(vm, &to, &from);
        } else {
            void* animations = g_ascii_manager->text_animations;
            void* created;
            state->handles[state->slot] = *AsHandle(RecoveryPlayerAnimationCreate(
                animations, &created, state->slot + 12, &entry->position));
            vm = IndicatorHandle_Get(state->handles[state->slot]);
            vm->font_width = 30;
            vm->font_height = 30;
            HintScalePair to = {
                entry->intensity * 0.75f, 0.0f
            };
            HintScalePair from = {
                entry->intensity * 0.5f, entry->intensity * 0.5f
            };
            StartScale(vm, &to, &from);
        }

        switch (entry->anchor_mode) {
        case 0:
            state->positions[state->slot] = vm->position;
            state->widths[state->slot] = entry->offset;
            vm->FormatCentered(g_sprt_ctrl, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            break;
        case 1:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x += entry->offset * 0.5f;
            state->widths[state->slot] = entry->offset;
            reinterpret_cast<RecoveryTextVm*>(vm)->MarkText(
                g_sprt_ctrl, 0x00FFFFFFu, static_cast<const char*>(entry->text));
            vm->flags = (vm->flags & 0xFFF7FFFFu) | 0x00040000u;
            break;
        case 2:
            state->positions[state->slot] = vm->position;
            state->positions[state->slot].x -= entry->offset * 0.5f;
            state->widths[state->slot] = entry->offset;
            vm->FormatRightAligned(g_sprt_ctrl, 0x00FFFFFFu, static_cast<const char*>(entry->text));
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
            recovery_indicator_free(entry);
    }
    return 0;
}
#pragma code_seg()
