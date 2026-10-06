#include "../../layout/ltcg/player_state_collision_runtime/effect_update.hpp"

// The shared record declares its handles volatile; the update reads them plainly.
#define REF(h) (*reinterpret_cast<AnimationRef*>(const_cast<unsigned int*>(&(h).value)))

// The actual complete 876-byte owner consumes one stack pointer and RET4.
// Descriptor callbacks have two real inputs in ECX/EDX. Private helpers
// above have complete definitions so LTCG chooses their internal registers.
#pragma code_seg(".text$f00428280F")
extern "C" __declspec(noinline) int __stdcall EffectPoolUpdate(PlayerState *player) {
    EffectEntry *effect = player->pickups;
    int remaining = 128;
    do {
        // The first two tests consume the same observed state word.
        int state = effect->state;
        if (state) {
            if (effect->descriptor->type == 3 && state == 1 &&
                (player->stage_timer.current < 0 ||
                 effect->descriptor->ordinal - 1 >= player->familiar_level)) {
                effect->handle.StopAtFrame1();
                effect->secondary_handle.StopAtFrame1();
                effect->state = 2;
                player->active_by_ordinal[effect->descriptor->ordinal] = 0;
            }
            if (effect->descriptor->type == 3 && effect->state == 1 &&
                ((data_0047770c && data_0047770c->script) || !data_00477704)) {
                effect->state = 2;
                effect->handle.StopAtFrame1();
                effect->secondary_handle.StopAtFrame1();
                player->active_by_ordinal[effect->descriptor->ordinal] = 0;
            }
            if (effect->descriptor->type == 3 && !effect->collected && effect->state == 1 &&
                effect->initialized == 1) {
                effect->handle.StopAtFrame3();
                effect->initialized = 0;
            }
            effect->collected = 0;
            if (effect->descriptor->effect_callback)
                effect->descriptor->effect_callback(player, effect);
            effect->motion.Update();
            effect->motion.Advance();
            AnimationContext *context = static_cast<AnimationContext*>(data_00491c10);
            AnimationObject *primary = context->FindInBuckets(REF(effect->handle));
            if (!primary) {
                effect->state = 0;
                AnimationRef secondary_id(effect->secondary_handle.value);
                AnimationObject *secondary = context->FindInBuckets(secondary_id);
                if (secondary) {
                    secondary->flags |= 0x4000000;
                    if (!secondary->child_previous)
                        for (AnimationNode *child = secondary->child_next; child;
                             child = child->next)
                            child->object->flags |= 0x4000000;
                }
                effect->secondary_handle.value = 0;
                effect->handle.value = 0;
                effect->secondary_handle.value = 0;
            } else if (effect->descriptor->type != 3 && effect->clock.current >= 10 &&
                       effect->motion.position.OutsideViewport(
                           primary->sprite->height * primary->scale_x,
                           primary->sprite->width * primary->scale_y)) {
                context->MarkForRemoval(REF(effect->handle));
                effect->handle.value = 0;
                effect->state = 0;
            } else {
                // Immutable retail screen origin: .rdata values 224.0 and 16.0.
                primary->position.x = effect->motion.position.x + 224.0f;
                primary->position.y = effect->motion.position.y + 16.0f;
                primary->position.z = effect->motion.position.z;
                if (REF(effect->secondary_handle).value) {
                    AnimationObject *secondary = context->Find(REF(effect->secondary_handle));
                    if (!secondary)
                        effect->secondary_handle.value = 0;
                    else {
                        secondary->position.x = effect->motion.position.x + 224.0f;
                        secondary->position.y = effect->motion.position.y + 16.0f;
                        secondary->position.z = effect->motion.position.z;
                    }
                }
                if (primary->flags & 0x8000000) {
                    primary->angle = effect->motion.angle;
                    primary->flags |= 4;
                }
                effect->clock.TickInline();
            }
        }
        ++effect;
    } while (--remaining);
    return 0;
}
#pragma code_seg()
