#include "th10/game/bullet_runtime_update.hpp"

namespace {

const uint32_t kImmediateBehaviors[] = {
    0x00000001u, 0x00000010u, 0x00000020u, 0x00000040u,
    0x00000100u, 0x00000080u, 0x08000c00u, 0x04000000u,
};

void Move(BulletRuntimeState* bullet, float scale) {
    for (int axis = 0; axis < 3; ++axis)
        bullet->position[axis] += bullet->velocity[axis] * scale;
}

}  // namespace

// 0x00406240 - Main bullet/entity update. The retail fastcall's ECX/EDX
// values are only forwarding scratch between behavior leaves; the persistent
// record is the explicit third argument.
int BulletRuntime_Update(BulletRuntimeState* bullet,
                         const BulletRuntimeHooks* hooks) {
    if ((bullet->flags & 8u) != 0) {
        hooks->destroy(hooks->context, bullet);
        return -1;
    }

    if (bullet->mode == 1) {
        hooks->prepare(hooks->context, bullet);
        if (bullet->behavior_flags != 0) {
            for (uint32_t bit : kImmediateBehaviors) {
                if ((bullet->behavior_flags & bit) != 0)
                    hooks->run_behavior(hooks->context, bullet, bit);
            }
            if ((bullet->behavior_flags & 0x8000u) != 0) {
                if (bullet->delayed_behavior_count < 1)
                    bullet->behavior_flags ^= 0x8000u;
                else
                    hooks->run_delayed_behavior(hooks->context, bullet);
            }
        }
        Move(bullet, hooks->frame_speed);
        if ((bullet->flags & 2u) != 0) {
            const int collision =
                hooks->collide_player(hooks->context, bullet);
            if (collision == 1) {
                bullet->mode = 3;
                bullet->animation_state = 1;
                if (bullet->collision_enabled >= 0)
                    hooks->cancel_animation(hooks->context, bullet);
            } else if (collision == 2 && (bullet->flags & 4u) == 0) {
                bullet->flags |= 4u;
                hooks->cancel_animation(hooks->context, bullet);
                hooks->play_cancel_sound(hooks->context);
            }
        }
    } else if (bullet->mode == 2) {
        Move(bullet, hooks->frame_speed * hooks->slow_scale);
        if (bullet->animation_state != 0) {
            bullet->mode = 1;
            return BulletRuntime_Update(bullet, hooks);
        }
    } else if (bullet->mode == 3) {
        Move(bullet, hooks->frame_speed * hooks->slow_scale);
    }

    if (bullet->collision_target != 0) {
        if ((bullet->behavior_flags & 0x100000u) != 0)
            hooks->run_target_behavior(hooks->context, bullet, 0x100000u);
        if ((bullet->behavior_flags & 0x200000u) != 0)
            hooks->run_target_behavior(hooks->context, bullet, 0x200000u);
        if (bullet->collision_delay < 1 &&
            hooks->target_outside(hooks->context, bullet)) {
            hooks->destroy(hooks->context, bullet);
            return -1;
        }
    }
    if (bullet->lifetime != 0) --bullet->lifetime;
    if (bullet->collision_delay > 0) --bullet->collision_delay;
    if (hooks->tick_animation(hooks->context, bullet) != 0) {
        hooks->destroy(hooks->context, bullet);
        return -1;
    }
    return 0;
}
