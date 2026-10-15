// 0x00428280: update the player's 128 bullets: move them, keep their
// animations in place, and retire lasers and bullets that left the screen.
#include "../../layout/ltcg/player_state_collision_runtime/effect_update.hpp"

// The shared record declares its handles volatile; the update reads them plainly.
#define REF(h) (*reinterpret_cast<AnimationRef*>(const_cast<unsigned int*>(&(h).value)))

// The actual complete 876-byte owner consumes one stack pointer and RET4.
// Descriptor callbacks have two real inputs in ECX/EDX. Private helpers
// above have complete definitions so LTCG chooses their internal registers.
#pragma code_seg(".text$f00428280F")
extern "C" __declspec(noinline) int __stdcall Player_UpdateBullets(Player* player) {
    PlayerBullet* bullet = player->bullets;
    int remaining = 128;
    do {
        // The first two tests consume the same observed state word.
        int state = bullet->state;
        if (state) {
            if (bullet->definition->kind == SHOT_LASER && state == 1 &&
                (player->shot_timer.current < 0 ||
                 bullet->definition->option - 1 >= player->option_count)) {
                bullet->animation.StopAtFrame1();
                bullet->laser_animation.StopAtFrame1();
                bullet->state = 2;
                player->laser_active[bullet->definition->option] = 0;
            }
            if (bullet->definition->kind == SHOT_LASER && bullet->state == 1 &&
                ((data_0047770c && data_0047770c->script) || !data_00477704)) {
                bullet->state = 2;
                bullet->animation.StopAtFrame1();
                bullet->laser_animation.StopAtFrame1();
                player->laser_active[bullet->definition->option] = 0;
            }
            if (bullet->definition->kind == SHOT_LASER && !bullet->hit_this_frame && bullet->state == 1 &&
                bullet->hitting == 1) {
                bullet->animation.StopAtFrame3();
                bullet->hitting = 0;
            }
            bullet->hit_this_frame = 0;
            if (bullet->definition->on_update)
                bullet->definition->on_update(player, bullet);
            bullet->motion.Update();
            bullet->motion.Advance();
            AnimationContext *context = static_cast<AnimationContext*>(data_00491c10);
            AnimationObject *primary = context->FindInBuckets(REF(bullet->animation));
            if (!primary) {
                bullet->state = 0;
                AnimationRef secondary_id(bullet->laser_animation.value);
                AnimationObject *secondary = context->FindInBuckets(secondary_id);
                if (secondary) {
                    secondary->flags |= 0x4000000;
                    if (!secondary->child_previous)
                        for (AnimationNode *child = secondary->child_next; child;
                             child = child->next)
                            child->object->flags |= 0x4000000;
                }
                bullet->laser_animation.value = 0;
                bullet->animation.value = 0;
                bullet->laser_animation.value = 0;
            } else if (bullet->definition->kind != SHOT_LASER && bullet->timer.current >= 10 &&
                       bullet->motion.position.OutsideViewport(
                           primary->sprite->height * primary->scale_x,
                           primary->sprite->width * primary->scale_y)) {
                context->MarkForRemoval(REF(bullet->animation));
                bullet->animation.value = 0;
                bullet->state = 0;
            } else {
                // Immutable retail screen origin: .rdata values 224.0 and 16.0.
                primary->position.x = bullet->motion.position.x + 224.0f;
                primary->position.y = bullet->motion.position.y + 16.0f;
                primary->position.z = bullet->motion.position.z;
                if (REF(bullet->laser_animation).value) {
                    AnimationObject *secondary = context->Find(REF(bullet->laser_animation));
                    if (!secondary)
                        bullet->laser_animation.value = 0;
                    else {
                        secondary->position.x = bullet->motion.position.x + 224.0f;
                        secondary->position.y = bullet->motion.position.y + 16.0f;
                        secondary->position.z = bullet->motion.position.z;
                    }
                }
                if (primary->flags & 0x8000000) {
                    primary->angle = bullet->motion.angle;
                    primary->flags |= 4;
                }
                bullet->timer.TickInline();
            }
        }
        ++bullet;
    } while (--remaining);
    return 0;
}
#pragma code_seg()
