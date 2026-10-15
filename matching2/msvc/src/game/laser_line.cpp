// 0x0041D3D0: execute the line laser's commands and motion callbacks,
// extend or consume the beam, test viewport/player contact, and tick its VMs.
#include "../../layout/ltcg/laser_line_0041d3d0/types.hpp"

// The lasers pass the player position as an oriented-rectangle point.
static inline const Point3_OrientedRect* PlayerPoint() {
    return reinterpret_cast<const Point3_OrientedRect*>(&g_player->position);
}

static __forceinline Point3_OrientedRect& LaserAddPosition(
        Point3_OrientedRect& point, const Point3_OrientedRect& delta) {
    point.x += delta.x;
    point.y += delta.y;
    point.z += delta.z;
    return point;
}

static __forceinline void LaserSetScaleComponent(float& component,
        unsigned int& flags, float value) {
    flags |= 8u;
    component = value;
}

#pragma code_seg(".text$10laser")
int LineLaser::Update() {
    RunCommands();
    if (flags) {
        // Each callback can change flags, so each following test reads again.
        if (flags & 1u) Motion0001();
        if (flags & 0x10u) Motion0010();
        if (flags & 0x20u) Motion0020();
        if (flags & 0x40u) Motion0040();
        if (flags & 0x100u) Motion0100();
        if (flags & 0x80u) Motion0080();
        if (flags & 0x08000c00u) Bounce();
        if (flags & 0x100000u) Motion100000();
        if (flags & 0x200000u) Motion200000();
        if (flags & 0x04000000u) Motion4000000();
        if (flags & 0x8000u) {
            if (flash_timer.current <= 0)
                flags ^= 0x8000u;
            else
                flash_timer.Advance(-1.0f);
        }
    }

    if (length < length_limit) {
        length += data_00476f78 * grow_speed;
        if (length > length_limit)
            length = length_limit;
    } else {
        // Once fully emitted, move the tail and reduce the remaining beam.
        traveled += data_00476f78 * grow_speed;
        Point3_OrientedRect delta(data_00476f78 * velocity.x,
            data_00476f78 * velocity.y, data_00476f78 * velocity.z);
        LaserAddPosition(position, delta);
        if (total_length > 0.0f && traveled + length > total_length) {
            length = total_length - traveled;
            length_limit = length;
            if (length <= 0.0f)
                return 1;
        }
    }

    if (hold_timer.current <= 0) {
        LinePosition head;
        head.SetPolar(angle, length);
        // The two-component polar boundary leaves the third stack word intact.
        LaserAddPosition(head, position);
        if (position.IsPartiallyOutside(width, width) &&
            head.IsPartiallyOutside(width, width))
            return 1;
    } else {
        hold_timer.Advance(-1.0f);
    }

    if (length > 16.0f && width > 3.0f) {
        LinePosition point;
        point.SetPolar(angle, length * 0.1f);
        point.x += position.x;
        point.y += position.y;
        point.z += position.z;
        float collision_width;
        // Unordered width takes the second branch, as in the retail test.
        if (width < 32.0f)
            collision_width = width * 0.5f;
        else
            collision_width = width - (width + 16.0f) * 0.5f;
        int collision = g_player->CheckLaserHit(&point,
            angle, collision_width, length * 0.800000011920929f);
        if (collision == 1) {
            Point3_OrientedRect hit_size(32.0f, 32.0f, 0.0f);
            OnPlayerHit(PlayerPoint(), &hit_size, 0);
        } else if (collision == 2 && age.current % 5 == 0) {
            void* handle;
            ItemAnimation_CreateOffset_00448db0(data_004776f0->resource,
                &handle, 434, PlayerPoint());
            data_00492590.QueuePan(28, position.x);
        }
    }

    LaserSprite* sprite = static_cast<LaserSprite*>(primary_animation.SpriteMetadata());
    Entity* animation = &primary_animation;
    LaserSetScaleComponent(animation->scale_x, animation->flags_35C,
        width / sprite->height);
    sprite = static_cast<LaserSprite*>(primary_animation.SpriteMetadata());
    LaserSetScaleComponent(animation->scale_y, animation->flags_35C,
        length / sprite->width);
    RunLaserAnimation_0043ee30(&primary_animation);
    if (traveled == 0.0f)
        RunLaserAnimation_0043ee30(&secondary_animation);
    return 0;
}
#pragma code_seg()
