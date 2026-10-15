// 0x00428630: the damage the player's bullets, bomb and damage sources deal
// to a box this frame (an enemy's position and size).
#include "../../../build_support/layout/ltcg/player_state_collision_runtime/runtime.hpp"
#include <math.h>
#pragma intrinsic(sin,cos)

template <class Center, class Size>
static __forceinline void GetBounds(const Center* center, const Size* size,
                                    Vec3* minimum, Vec3* maximum) {
    minimum->x = center->x - size->x * 0.5f;
    minimum->y = center->y - size->y * 0.5f;
    maximum->x = center->x + size->x * 0.5f;
    maximum->y = center->y + size->y * 0.5f;
}

#pragma code_seg(".text$f00428630F")
int PlayerDamage::Sweep(Player* player, const PickupPoint* center,
                            const PickupPoint* size) {
    int total = 0;
    if (player->state_timer.current == player->state_timer.previous) return 0;
    PlayerBullet* bullet = player->bullets;

    Vec3 minimum, maximum, working_point;
    GetBounds(center, size, &minimum, &maximum);
    if (this) value = 0;
    for (int count = 128; count != 0; --count, ++bullet) {
        int state=bullet->state;
        if (state == 0 || state == 2) continue;
        ShotDefinition* shot = bullet->definition;
        Vec3 pickup_minimum;
        GetBounds(&bullet->motion.position,
                  reinterpret_cast<const PickupPoint*>(&shot->width),
                  &pickup_minimum, &working_point);
        if (pickup_minimum.y > maximum.y || pickup_minimum.x > maximum.x ||
            working_point.y < minimum.y || working_point.x < minimum.x)
            continue;
        if (shot->kind != SHOT_LASER && pickup_minimum.y < 0.0f) continue;
        if (shot->kind == SHOT_LASER && maximum.y < 0.0f) continue;
        if (shot->skip_hit && shot->skip_hit(player,bullet,center)) continue;
        if (!bullet->hitting) {
            bullet->animation.StopAtFrame2();
            bullet->hitting = 1;
        }
        shot = bullet->definition;
        bullet->hit_this_frame = 1;
        if (shot->kind != SHOT_LASER || bullet->timer.AtInterval(4)) total += shot->damage;
        if (shot->kind != SHOT_LASER) {
            float saved_angle = bullet->animation.Validate()->angle;
            bullet->animation.Retire();
            bullet->animation.value = Pickup_CreatePrimaryBack(
                player->animation_file, bullet->definition->hit_animation + 5, 15).value;
            PickupAnimation* object = bullet->animation.Validate();
            object->angle = saved_angle;
            object->flags |= 4u;
            bullet->motion.position.z = 0.1f;
            bullet->state = 2;
            bullet->motion.speed *= 0.125f;
        }
        shot = bullet->definition;
        if (shot->kind == SHOT_HOMING) {
            int indicator_value = shot->damage/3;
            Player_AddDamageSource(shot->damage,player,&bullet->motion.position,
                                     0x42000000u,0x3fb33333u,13,indicator_value);
        }
    }
    total += g_bomb->HitTest(center);
    PlayerDamageSource* circle = player->damage_sources;
    PlayerDamageSource* table = circle;
    for (int index = 0; index < 32; ++circle, ++index) {
        PlayerDamageSource* region = &table[index];
        if (!(region->flags & 1u)) continue;
        if (region->lifetime.current != region->lifetime.previous &&
            region->lifetime.current % region->interval == 0) continue;
        if (!(region->flags & 2u)) {
            if (region->angle == 0.0f) {
                float half_width = region->width * 0.5f;
                if (region->position.x - half_width > maximum.x ||
                    region->position.x + half_width < minimum.x) continue;
                float half_height = region->height * 0.5f;
                if (region->position.y - half_height > maximum.y ||
                    region->position.y + half_height < minimum.y) continue;
            } else {
                double dx = center->x - region->position.x;
                double dy = center->y - region->position.y;
                float sine = sinf(-region->angle);
                double cosine = cos(-region->angle);
                working_point.x = cosine * dx - sine * dy;
                working_point.y = sine * dx + cosine * dy;
                float half_x = size->x * 0.5f;
                if (region->width * -0.5f > half_x + working_point.x ||
                    region->width * 0.5f < working_point.x - half_x) continue;
                float half_y = size->y * 0.5f;
                if (region->height * -0.5f > half_y + working_point.y ||
                    region->height * 0.5f < working_point.y - half_y) continue;
            }
        } else {
            float radius = circle->radius;
            float dy = region->position.y - center->y;
            float dx = region->position.x - center->x;
            if (radius * radius < dx * dx + dy * dy) continue;
        }
        total += region->damage;
        region->damage_dealt += region->damage;
        if (region->damage_limit <= region->damage_dealt) region->damage = 0;
    }
    if (total != 0) {
        data_00474c44 += (total/10+10)/10;
        if (data_00474c44 >= 1000000000) data_00474c44 = 999999999;
    }
    return total;
}
#pragma code_seg()
