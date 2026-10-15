// 0x00427E90: fire one shot from the first free bullet slot.
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/effect_update.hpp"
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/animation_public_callers.hpp"
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/sound_queue.hpp"

// Looks an animation up by handle and clears a stale handle.
static __forceinline AnimationObject* ResolveOrClear(unsigned int* handle) {
    unsigned int value = *handle;
    AnimationObject* object = static_cast<AnimationContext*>(g_sprt_ctrl)->FindInBuckets(value);
    if (!object) *handle = 0;
    return object;
}

// A fixed-point position as a world position at depth 0.
static __forceinline Vector3 ToWorldPosition(const FixedPoint& point) {
    Vector3 value = {point.x * 0.01f, point.y * 0.01f, 0.0f};
    return value;
}

#pragma code_seg(".text$f00427e90F")
extern "C" __declspec(noinline) int __stdcall Player_FireShot(
        Player* player, ShotDefinition* shot, int frame) {
    PlayerBullet* bullet = player->bullets;
    if (shot->kind == SHOT_LASER && player->laser_active[shot->option])
        return 0;
    for (int index = 0; index < 128; ++index, ++bullet) {
        if (bullet->state == 0) {
            bullet->state = 1;
            bullet->definition = shot;
            if (!(bullet->timer.flags & 1)) {
                bullet->timer.current = 0;
                bullet->timer.previous = -999999;
                bullet->timer.elapsed = 0.0f;
                bullet->timer.speed = &g_score_default_speed;
                bullet->timer.flags |= 1;
            }
            bullet->timer.current = 0;
            bullet->timer.elapsed = 0.0f;
            bullet->timer.previous = -1;
            if (shot->option == 0) {
                bullet->motion.position = player->position;
            } else {
                PlayerOption* option = &player->options[shot->option - 1];
                bullet->motion.position = ToWorldPosition(option->position);
            }
            if (shot->kind == SHOT_LASER)
                player->laser_active[shot->option] = 1;
            bullet->motion.speed = shot->speed;
            bullet->motion.angle = NormalizeAngle(shot->angle);
            bullet->motion.Update();
            bullet->motion.position.x += shot->offset.x - bullet->motion.velocity.x;
            bullet->motion.position.y += shot->offset.y - bullet->motion.velocity.y;

            int script = shot->animation + 5;
            void* resource = player->animation_file;
            Entity* object = static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
            unsigned int flags = object->flags_35C;
            object->render_bucket = 15;
            object->flags_35C = flags | 0x40000000u;
            static_cast<AnimationResource_00449870*>(resource)
                ->InitializeObject(object, script);
            AnimationRef id = static_cast<AnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
            // The shared record declares its handles volatile for the bullet update.
            const_cast<unsigned int&>(bullet->animation.value) = id.value;
            AnimationObject* primary = ResolveOrClear(const_cast<unsigned int*>(&bullet->animation.value));
            if (primary->flags & 0x8000000) {
                primary->angle = shot->angle;
                primary->flags |= 4;
            }
            if (shot->kind == SHOT_LASER) {
                void* laser_resource = player->animation_file;
                Entity* laser = static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
                unsigned int laser_flags = laser->flags_35C;
                laser->render_bucket = 15;
                laser->flags_35C = laser_flags | 0x40000000u;
                static_cast<AnimationResource_00449870*>(laser_resource)
                    ->InitializeObject(laser, 16);
                AnimationRef laser_id = static_cast<AnimationLists*>(g_sprt_ctrl)
                    ->RegisterPrimaryBack(laser);
                bullet->laser_animation.value = laser_id.value;
            } else {
                bullet->laser_animation.value = 0;
            }
            if (shot->on_fire)
                shot->on_fire(player, bullet, frame);
            if (shot->sound >= 0)
                g_sound_manager.QueuePan(shot->sound, bullet->motion.position.x);
            return 0;
        }
    }
    return 0;
}
#pragma code_seg()
