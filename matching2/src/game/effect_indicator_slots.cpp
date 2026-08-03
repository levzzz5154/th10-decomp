#include "th10/game/effect_indicator_slots.hpp"

#include <cstring>

extern float DAT_00476f78;  // default timer speed sentinel (1.0f)

namespace {

// Retail stores (float)frames into the timer's previous word; keep the
// exact bit image in the integer field.
void StoreFloatImage(int* slot, float value) {
    memcpy(slot, &value, sizeof(value));
}

}  // namespace

// 0x0042A930 - Arm an embedded countdown timer. The first-use branch is
// the shared five-word sentinel pattern (see EmbeddedTimer_Reset at
// 0x004050D0): seed target with -999999, wire the speed pointer to the
// global default, and set the initialized bit.
void EmbeddedTimer_SetCountdown(EmbeddedTimerState* timer, int32_t frames) {
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = (int)0xFFF0BDC1;  // -999999 first-use sentinel
        timer->previous = 0;
        timer->speed = &DAT_00476f78;
        timer->flags |= 1u;
    }
    timer->current = frames;
    timer->target = frames - 1;
    StoreFloatImage(&timer->previous, (float)frames);
}

// 0x00427B50 - Allocate the first free indicator slot. Retail walks the
// 0x20 slots at manager+0x350C (0x1B words each) and takes the first
// one whose in-use bit is clear: wipe the whole slot, set flag bits
// 0 and 1, clear the 0xB-word tail region again (dead after the wipe),
// copy the position triple, store kind and argument, arm the embedded
// timer (its flags were just wiped, so the sentinel branch always
// runs), and apply the mode / counter / limit / phase defaults.
EffectIndicatorSlot* EffectIndicatorPool_Allocate(EffectIndicatorPool* pool,
                                                  const float position[3],
                                                  uint32_t kind,
                                                  uint32_t argument,
                                                  int32_t frames,
                                                  uint32_t mode) {
    for (int index = 0; index < 0x20; ++index) {
        EffectIndicatorSlot* slot = &pool->slots[index];
        if ((slot->flags & 1u) != 0) {
            continue;
        }
        memset(slot, 0, sizeof(*slot));
        slot->flags |= 3u;
        slot->x = position[0];
        slot->y = position[1];
        slot->z = position[2];
        slot->kind = kind;
        slot->argument = argument;
        EmbeddedTimer_SetCountdown(&slot->timer, frames);
        slot->mode = mode;
        slot->counter = 0;
        slot->limit = 999999;
        slot->phase = 4;
        return slot;
    }
    // Retail falls off the loop with the cursor one entry past the pool
    // and returns it unchanged.
    return &pool->slots[0x20];
}

// 0x00427D80 - Multiply an integer pair into an output pair, reading
// both inputs before the first store like the retail body.
#ifdef _MSC_VER
__declspec(naked) void CellPair_Scale(int32_t out[2], const int32_t pair[2],
                                      int32_t scale) {
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esi+4]
        mov esi, [esi]
        imul ecx, edx
        imul esi, edx
        mov [eax], esi
        mov [eax+4], ecx
        pop esi
        ret
    }
}
#else
void CellPair_Scale(int32_t out[2], const int32_t pair[2], int32_t scale) {
    const int32_t second = pair[1];
    out[0] = pair[0] * scale;
    out[1] = second * scale;
}
#endif


// 0x00427E90 - Materialize a descriptor selected by the caller at 0x00428160
// into the first inactive 0x5C-byte watch slot. The slot is intentionally not
// cleared: retail preserves its polar carry fields and mode bit across reuse.
int EffectWatch_SpawnFromDescriptor(EffectWatchManager* manager,
                                    const EffectWatchDescriptor* descriptor,
                                    int callback_argument,
                                    const EffectWatchEnvironment* environment) {
    const int source = descriptor->source_index;
    if (descriptor->mode == 3 && manager->exclusive_active[source] != 0) {
        return 0;
    }

    EffectWatchSlot* slot = 0;
    for (int index = 0; index < 0x80; ++index) {
        if (manager->slots[index].active == 0) {
            slot = &manager->slots[index];
            break;
        }
    }
    if (slot == 0) {
        return 0;
    }

    slot->active = 1;
    slot->descriptor = descriptor;
    if ((slot->timer.flags & 1u) == 0) {
        slot->timer.current = 0;
        slot->timer.target = (int)0xFFF0BDC1;
        slot->timer.previous = 0;
        slot->timer.speed = &DAT_00476f78;
        slot->timer.flags |= 1u;
    }
    slot->timer.current = 0;
    slot->timer.previous = 0;
    slot->timer.target = -1;

    if (source == 0) {
        slot->origin[0] = manager->player_position[0];
        slot->origin[1] = manager->player_position[1];
        slot->origin[2] = manager->player_position[2];
    } else {
        slot->origin[0] = manager->sources[source].x_hundredths * 0.01f;
        slot->origin[1] = manager->sources[source].y_hundredths * 0.01f;
        slot->origin[2] = 0.0f;
    }

    if (descriptor->mode == 3) {
        manager->exclusive_active[source] = 1;
    }
    slot->radius = descriptor->radius;
    slot->angle = environment->normalize_angle(descriptor->angle);
    if ((slot->flags & 1u) == 0) {
        environment->set_polar(slot->polar, slot->angle, slot->radius);
        slot->polar[2] = 0.0f;
    } else {
        slot->phase += slot->phase_delta;
        slot->angle = environment->normalize_angle(slot->radius + slot->angle);
    }
    slot->origin[0] += descriptor->offset_x - slot->polar[0];
    slot->origin[1] += descriptor->offset_y - slot->polar[1];

    void* primary = environment->allocate_vm(environment->context);
    environment->prepare_vm(environment->context, primary, 15, 0x40000000u,
                            manager->animation_owner,
                            descriptor->script_index + 5);
    slot->primary_handle =
        environment->register_vm(environment->context, primary);
    void* resolved =
        environment->find_vm(environment->context, slot->primary_handle);
    if (resolved == 0) {
        // Retail assumes the just-registered VM resolves successfully. Keep the
        // readable recovery safe while preserving the zero-handle fallback.
        slot->primary_handle = 0;
    } else if ((environment->get_vm_flags(environment->context, resolved) &
                0x08000000u) != 0) {
        environment->set_vm_angle_and_flags(environment->context, resolved,
                                            descriptor->angle, 4u);
    }

    if (descriptor->mode == 3) {
        void* secondary = environment->allocate_vm(environment->context);
        environment->prepare_vm(environment->context, secondary, 15,
                                0x40000000u, manager->animation_owner, 0x10);
        slot->secondary_handle =
            environment->register_vm(environment->context, secondary);
    } else {
        slot->secondary_handle = 0;
    }

    if (descriptor->callback != 0) {
        descriptor->callback(manager, slot, callback_argument);
    }
    if (descriptor->sound_id >= 0 && environment->queue_sound != 0) {
        environment->queue_sound(environment->context, descriptor->sound_id,
                                 slot->origin[0]);
    }
    return 0;
}
