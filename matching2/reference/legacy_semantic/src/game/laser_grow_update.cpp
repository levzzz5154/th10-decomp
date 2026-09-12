#include "th10/game/laser_grow_update.hpp"

#include <cmath>

namespace {

const unsigned int kFollowPlayer = 1;
const unsigned int kRenderScaleDirty = 8;
const int kWaitingState = 3;
const int kGrowingState = 4;
const int kActiveState = 2;
const int kShrinkingState = 5;
const float kCollisionLengthStart = 16.0f;

void ResetTimer(GrowLaser* laser) {
    laser->timer_current = 0;
    laser->timer_elapsed = 0.0f;
}

void UpdateCollision(GrowLaser* laser, const GrowLaserEnv* env) {
    if ((laser->state != kGrowingState &&
         laser->state != kActiveState) ||
        laser->length <= kCollisionLengthStart) {
        return;
    }

    const float center_offset = laser->length * 0.1f;
    float collision_position[3] = {
        laser->position[0] + std::cos(laser->angle) * center_offset,
        laser->position[1] + std::sin(laser->angle) * center_offset,
        laser->position[2]
    };
    const float half_width = laser->width >= 32.0f
        ? laser->width - (laser->width + 16.0f) * 0.33333334f
        : laser->width * 0.5f;

    const int collision = env->collision_test(
        collision_position, laser->angle, half_width,
        laser->length * 0.80000001f);
    if (collision == 1) {
        env->on_player_hit(laser);
    } else if (collision == 2 && laser->timer_current % 5 == 0) {
        env->on_graze_effect(laser);
    }
}

}  // namespace

// 0x0041E700 - Advance laser growth and motion, run the wait/grow/hold/shrink
// state machine, test active beam collision, and update both render VMs.
int Laser_UpdateState(GrowLaser* laser,
                      const GrowLaserEnv* env) {
    if (laser->length < laser->target_length) {
        laser->length += env->game_speed * laser->length_growth;
        if (laser->length > laser->target_length) {
            laser->length = laser->target_length;
        }
    }

    laser->angle = env->add_normalized_angle(
        laser->angle, env->game_speed * laser->angular_velocity);

    if ((laser->flags & kFollowPlayer) && env->player_position != 0) {
        for (int axis = 0; axis < 3; ++axis) {
            laser->position[axis] = env->player_position[axis];
        }
    }
    for (int axis = 0; axis < 3; ++axis) {
        laser->position[axis] +=
            env->game_speed * laser->velocity[axis];
    }

    switch (laser->state) {
    case kWaitingState:
        if (laser->timer_current >= laser->wait_frames) {
            ResetTimer(laser);
            laser->state = kGrowingState;
        }
        break;

    case kGrowingState:
        if (laser->timer_current < laser->grow_frames) {
            laser->width = laser->target_width * laser->timer_elapsed /
                           laser->grow_frames;
            break;
        }
        ResetTimer(laser);
        laser->state = kActiveState;
        laser->width = laser->target_width;
        /* fall through */
    case kActiveState:
        if (laser->timer_current >= laser->hold_frames) {
            ResetTimer(laser);
            laser->state = kShrinkingState;
        }
        break;

    case kShrinkingState:
        if (laser->timer_current >= laser->shrink_frames) {
            return 1;
        }
        laser->width = laser->target_width -
            laser->target_width * laser->timer_elapsed /
            laser->shrink_frames;
        break;
    }

    UpdateCollision(laser, env);

    laser->render_scale[0] = laser->width / laser->sprite_height;
    laser->render_scale[1] = laser->length / laser->sprite_width;
    laser->render_flags |= kRenderScaleDirty;
    env->update_primary_vm(laser);
    if (laser->secondary_render_gate == 0.0f) {
        env->update_secondary_vm(laser);
    }
    return 0;
}
