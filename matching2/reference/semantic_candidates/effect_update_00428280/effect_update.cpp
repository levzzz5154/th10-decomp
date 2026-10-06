#include "effect_update.hpp"

static __forceinline AnimationObject *FindInBuckets(AnimationContext *context, AnimationId id) {
    if (!id.value)
        return 0;
    for (AnimationNode *node = context->primary; node; node = node->next)
        if (node->object->id == id.value)
            return node->object;
    for (AnimationNode *node = context->secondary; node; node = node->next)
        if (node->object->id == id.value)
            return node->object;
    return 0;
}

#pragma code_seg(".text$a40find")
__declspec(noinline)
AnimationObject *__fastcall FindAnimation(AnimationContext *context, AnimationId id) {
    return FindInBuckets(context, id);
}
#pragma code_seg()
#pragma code_seg(".text$a50flag")
__declspec(noinline) void *__fastcall FlagAnimation(AnimationContext *context, AnimationId id) {
    AnimationObject *object = FindAnimation(context, id);
    if (object) {
        object->flags |= 0x4000000;
        if (!object->child_previous) {
            AnimationNode *child = object->child_next;
            for (; child; child = child->next)
                child->object->flags |= 0x4000000;
            return child;
        }
    }
    return object;
}
#pragma code_seg()
#pragma code_seg(".text$a10stop1")
void Handle::StopAtFrame1() {
    AnimationId id = {value};
    AnimationObject *object = FindAnimation(data_00491c10, id);
    if (object) {
        object->stop_frame = 1;
        if (!object->child_previous)
            for (AnimationNode *child = object->child_next; child; child = child->next)
                child->object->stop_frame = 1;
    }
}
#pragma code_seg()
#pragma code_seg(".text$a20stop3")
void Handle::StopAtFrame3() {
    AnimationId id = {value};
    AnimationObject *object = FindAnimation(data_00491c10, id);
    if (object) {
        object->stop_frame = 3;
        if (!object->child_previous)
            for (AnimationNode *child = object->child_next; child; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg()
#pragma code_seg(".text$a60motion")
void Motion::Advance() {
    Vec3 offset;
    if (!(flags & 1)) {
        position += velocity;
        position.SnapToHundredths();
        return;
    }
    offset.SetPolar(angle, radius);
    offset.z = 0.0f;
    position = offset + velocity;
    position.SnapToHundredths();
}
#pragma code_seg()

inline void Motion::Update() {
    if (!(flags & 1)) {
        velocity.SetPolar(angle, speed);
        velocity.z = 0.0f;
    } else {
        radius += radius_step;
        angle = NormalizeAngle(speed + angle);
    }
}

extern "C" const float data_00470b40, data_00470b3c, data_00470b04, data_00470b38;
#pragma code_seg(".text$a70bounds")
int Vec3::OutsideViewport(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= data_00470b40) && !(x - horizontal_margin >= data_00470b3c) &&
        !(y + vertical_margin <= data_00470b04) && !(y - vertical_margin >= data_00470b38))
        return 0;
    return 1;
}
#pragma code_seg()

// The actual complete 876-byte owner consumes one stack pointer and RET4.
// Descriptor callbacks have two real inputs in ECX/EDX. Private helpers
// above have complete definitions so LTCG chooses their internal registers.
#pragma code_seg(".text$a30update")
extern "C" __declspec(noinline) int __stdcall EffectPoolUpdate(PlayerState *player) {
    EffectEntry *effect = player->effects;
    int remaining = 128;
    do {
        // The first two tests consume the same observed state word.
        int state = effect->state;
        if (state) {
            if (effect->descriptor->kind == 3 && state == 1 &&
                (player->stage_timer.current < 0 ||
                 effect->descriptor->ordinal - 1 >= player->familiar_level)) {
                effect->primary.StopAtFrame1();
                effect->secondary.StopAtFrame1();
                effect->state = 2;
                player->active_by_ordinal[effect->descriptor->ordinal] = 0;
            }
            if (effect->descriptor->kind == 3 && effect->state == 1 &&
                ((data_0047770c && data_0047770c->script) || !data_00477704)) {
                effect->state = 2;
                effect->primary.StopAtFrame1();
                effect->secondary.StopAtFrame1();
                player->active_by_ordinal[effect->descriptor->ordinal] = 0;
            }
            if (effect->descriptor->kind == 3 && !effect->touched && effect->state == 1 &&
                effect->started == 1) {
                effect->primary.StopAtFrame3();
                effect->started = 0;
            }
            effect->touched = 0;
            if (effect->descriptor->callback)
                effect->descriptor->callback(player, effect);
            effect->motion.Update();
            effect->motion.Advance();
            AnimationContext *context = data_00491c10;
            AnimationId primary_id = {effect->primary.value};
            AnimationObject *primary = FindInBuckets(context, primary_id);
            if (!primary) {
                effect->state = 0;
                AnimationId secondary_id = {effect->secondary.value};
                AnimationObject *secondary = FindInBuckets(context, secondary_id);
                if (secondary) {
                    secondary->flags |= 0x4000000;
                    if (!secondary->child_previous)
                        for (AnimationNode *child = secondary->child_next; child;
                             child = child->next)
                            child->object->flags |= 0x4000000;
                }
                effect->secondary.value = 0;
                effect->primary.value = 0;
                effect->secondary.value = 0;
            } else if (effect->descriptor->kind != 3 && effect->timer.current >= 10 &&
                       effect->motion.position.OutsideViewport(
                           primary->sprite->height * primary->scale_x,
                           primary->sprite->width * primary->scale_y)) {
                AnimationId id = {effect->primary.value};
                FlagAnimation(context, id);
                effect->primary.value = 0;
                effect->state = 0;
            } else {
                // Immutable retail screen origin: .rdata values 224.0 and 16.0.
                primary->position.x = effect->motion.position.x + 224.0f;
                primary->position.y = effect->motion.position.y + 16.0f;
                primary->position.z = effect->motion.position.z;
                // One handle read supplies both the test and the lookup.
                int secondary_value = effect->secondary.value;
                if (secondary_value) {
                    AnimationId id = {secondary_value};
                    AnimationObject *secondary = FindAnimation(context, id);
                    if (!secondary)
                        effect->secondary.value = 0;
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
                effect->timer.TickInline();
            }
        }
        ++effect;
    } while (--remaining);
    return 0;
}
#pragma code_seg()
