// 0x0041E700: advance a growing laser, test player collision and graze,
// and update its two animation VMs. The complete 832-byte region includes
// the four-entry phase switch table at 0x0041EA30.
#include "../../../build_support/layout/ltcg/laser_grow/types.hpp"

// The lasers pass the player position as an oriented-rectangle point.
static inline const Point3_OrientedRect* PlayerPoint() {
    return reinterpret_cast<const Point3_OrientedRect*>(&g_player->position);
}

static __forceinline void LaserSetScaleComponent(float& component,
        unsigned int& flags, float value) {
    flags |= 8u;
    component = value;
}

static __forceinline Point3_OrientedRect& LaserAddPosition(
        Point3_OrientedRect& point, const Point3_OrientedRect& delta) {
    point.x += delta.x;
    point.y += delta.y;
    point.z += delta.z;
    return point;
}

#pragma code_seg(".text$20laser")
int GrowLaser::Update() {
    if (length < target_length) {
        length += g_game_speed * length_growth;
        if (length > target_length)
            length = target_length;
    }
    angle = NormalizeAngle2(angle, g_game_speed * angular_velocity);
    if ((flags & 1u) && g_enemy_ctrl->target)
        position = g_enemy_ctrl->target->position;

    Point3_OrientedRect delta(g_game_speed * velocity.x,
        g_game_speed * velocity.y, g_game_speed * velocity.z);
    LaserAddPosition(position, delta);

    switch (state) {
    case 3: // Waiting for growth to start.
        if (timer.current >= wait_frames) {
            timer.Set(0);
            state = 4;
        }
        break;
    case 4: // Growing toward the full beam width.
        if (timer.current >= grow_frames) {
            timer.Set(0);
            state = 2;
            width = target_width;
        } else {
            width = target_width * timer.elapsed / grow_frames;
            break;
        }
        // Grow completion immediately tests the active phase.
    case 2: // Holding the full beam width.
        if (timer.current < hold_frames)
            break;
        timer.Set(0);
        state = 5;
        // Active completion immediately tests the shrinking phase.
    case 5: // Shrinking until the laser can be retired.
        if (timer.current >= shrink_frames)
            return 1;
        {
            float full_width = target_width;
            width = full_width - full_width * timer.elapsed / shrink_frames;
        }
        break;
    }

    if ((state == 4 || state == 2) && length > 16.0f) {
        LaserPolarPoint point;
        point.SetPolar(angle, length * 0.1f);
        point.x += position.x;
        point.y += position.y;
        // Retail reads this third stack word after its two-component setter.
        point.z += position.z;

        float collision_width;
        // An unordered comparison takes the second branch, as in retail.
        if (width < 32.0f)
            collision_width = width * 0.5f;
        else
            collision_width = width - (width + 16.0f) * 0.3333333432674408f;
        int collision = g_player->CheckLaserHit(&point,
            angle, collision_width, length * 0.800000011920929f);
        if (collision == 1) {
            Point3_OrientedRect hit_size(32.0f, 32.0f, 0.0f);
            OnPlayerHit(PlayerPoint(), &hit_size, 0);
        } else if (collision == 2 && timer.current % 5 == 0) {
            void* handle;
            ItemAnimation_CreateOffset(g_bullet_manager->resource,
                &handle, 434, PlayerPoint());
            g_sound_manager.QueuePan(28, position.x);
        }
    }

    LaserSprite* sprite = static_cast<LaserSprite*>(primary_animation.SpriteMetadata());
    Entity* animation = &primary_animation;
    LaserSetScaleComponent(animation->scale_x, animation->flags_35C,
        width / sprite->height);
    sprite = static_cast<LaserSprite*>(primary_animation.SpriteMetadata());
    LaserSetScaleComponent(animation->scale_y, animation->flags_35C,
        length / sprite->width);
    RunLaserAnimation(&primary_animation);
    if (secondary_render_gate == 0.0f)
        RunLaserAnimation(&secondary_animation);
    return 0;
}
#pragma code_seg()
