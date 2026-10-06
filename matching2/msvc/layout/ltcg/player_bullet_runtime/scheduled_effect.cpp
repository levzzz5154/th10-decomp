#include "effect_update.hpp"
#include "animation_public_callers.hpp"
#include "sound_queue.hpp"

#pragma code_seg(".text$f00427e90F")
extern "C" __declspec(noinline) int __stdcall StageSchedule_Fire_00427e90(
        PlayerState* player, PickupDescriptor* descriptor, int frame) {
    PickupRecord* effect = player->pickups;
    if (descriptor->type == 3 && player->active_by_ordinal[descriptor->ordinal])
        return 0;
    for (int index = 0; index < 128; ++index, ++effect) {
        if (effect->state == 0) {
            effect->state = 1;
            effect->descriptor = descriptor;
            if (!(effect->clock.flags & 1)) {
                effect->clock.current = 0;
                effect->clock.previous = -999999;
                effect->clock.elapsed = 0.0f;
                effect->clock.speed = &g_score_default_speed;
                effect->clock.flags |= 1;
            }
            effect->clock.current = 0;
            effect->clock.elapsed = 0.0f;
            effect->clock.previous = -1;
            if (descriptor->ordinal == 0) {
                effect->motion.position = player->spawn_origin;
            } else {
                ScheduledFamiliar* familiar = &player->familiars[descriptor->ordinal - 1];
                effect->motion.position = familiar->position.ToWorldPosition();
            }
            if (descriptor->type == 3)
                player->active_by_ordinal[descriptor->ordinal] = 1;
            effect->motion.speed = descriptor->spawn_speed;
            effect->motion.angle = NormalizeAngle(descriptor->spawn_angle);
            effect->motion.Update();
            effect->motion.position.x += descriptor->spawn_offset.x - effect->motion.velocity.x;
            effect->motion.position.y += descriptor->spawn_offset.y - effect->motion.velocity.y;

            int script = descriptor->spawn_script + 5;
            void* resource = player->animation_resource;
            Entity* object = static_cast<AnimationPool*>(data_00491c10)->Allocate();
            unsigned int flags = object->flags_35C;
            object->render_bucket = 15;
            object->flags_35C = flags | 0x40000000u;
            static_cast<AnimationResource_00449870*>(resource)
                ->InitializeObject(object, script);
            AnimationRef id = static_cast<AnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
            effect->handle.value = id.value;
            AnimationObject* primary = static_cast<AnimationContext*>(data_00491c10)->FindInBuckets(id);
            if (!primary) effect->handle.value = 0;
            if (primary->flags & 0x8000000) {
                primary->angle = descriptor->spawn_angle;
                primary->flags |= 4;
            }
            if (descriptor->type == 3) {
                void* secondary_resource = player->animation_resource;
                Entity* secondary = static_cast<AnimationPool*>(data_00491c10)->Allocate();
                unsigned int secondary_flags = secondary->flags_35C;
                secondary->render_bucket = 15;
                secondary->flags_35C = secondary_flags | 0x40000000u;
                static_cast<AnimationResource_00449870*>(secondary_resource)
                    ->InitializeObject(secondary, 16);
                AnimationRef secondary_id = static_cast<AnimationLists*>(data_00491c10)
                    ->RegisterPrimaryBack(secondary);
                effect->secondary_handle.value = secondary_id.value;
            } else {
                effect->secondary_handle.value = 0;
            }
            if (descriptor->spawn_callback)
                descriptor->spawn_callback(player, effect, frame);
            if (descriptor->spawn_sound >= 0)
                data_00492590.QueuePan(descriptor->spawn_sound, effect->motion.position.x);
            return 0;
        }
    }
    return 0;
}
#pragma code_seg()
