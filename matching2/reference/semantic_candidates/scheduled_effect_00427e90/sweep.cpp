#include "runtime.hpp"
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

#pragma code_seg(".text$20sweep")
int PickupSweepResult::Sweep(PickupManager* manager, const PickupPoint* center,
                            const PickupPoint* size) {
    int total = 0;
    if (manager->state_timer.current == manager->state_timer.previous) return 0;
    PickupRecord* pickup = manager->pickups;

    Vec3 minimum, maximum, working_point;
    GetBounds(center, size, &minimum, &maximum);
    if (this) value = 0;
    for (int count = 128; count != 0; --count, ++pickup) {
        int state=pickup->state;
        if (state == 0 || state == 2) continue;
        PickupDescriptor* descriptor = pickup->descriptor;
        Vec3 pickup_minimum;
        GetBounds(&pickup->motion.position,
                  reinterpret_cast<const PickupPoint*>(&descriptor->width),
                  &pickup_minimum, &working_point);
        if (pickup_minimum.y > maximum.y || pickup_minimum.x > maximum.x ||
            working_point.y < minimum.y || working_point.x < minimum.x)
            continue;
        if (descriptor->type != 3 && pickup_minimum.y < 0.0f) continue;
        if (descriptor->type == 3 && maximum.y < 0.0f) continue;
        if (descriptor->filter && descriptor->filter(manager,pickup,center)) continue;
        if (!pickup->initialized) {
            pickup->handle.StopAtFrame2();
            pickup->initialized = 1;
        }
        descriptor = pickup->descriptor;
        pickup->collected = 1;
        if (descriptor->type != 3 || pickup->clock.AtInterval(4)) total += descriptor->value;
        if (descriptor->type != 3) {
            float saved_angle = pickup->handle.Validate()->angle;
            pickup->handle.Retire();
            pickup->handle.value = Pickup_CreatePrimaryBack(
                manager->animation_resource, pickup->descriptor->collected_script + 5, 15).value;
            PickupAnimation* object = pickup->handle.Validate();
            object->angle = saved_angle;
            object->flags |= 4u;
            pickup->motion.position.z = 0.1f;
            pickup->state = 2;
            pickup->motion.speed *= 0.125f;
        }
        descriptor = pickup->descriptor;
        if (descriptor->type == 2) {
            int indicator_value = descriptor->value/3;
            Pickup_AllocateIndicator(descriptor->value,manager,&pickup->motion.position,
                                     0x42000000u,0x3fb33333u,13,indicator_value);
        }
    }
    total += data_004776ec->HitTest(center);
    PickupRegion* circle = manager->regions;
    PickupRegion* table = circle;
    for (int index = 0; index < 32; ++circle, ++index) {
        PickupRegion* region = &table[index];
        if (!(region->flags & 1u)) continue;
        if (region->timer.current != region->timer.previous &&
            region->timer.current % region->interval == 0) continue;
        if (!(region->flags & 2u)) {
            if (region->angle == 0.0f) {
                float half_width = region->width * 0.5f;
                if (region->center.x - half_width > maximum.x ||
                    region->center.x + half_width < minimum.x) continue;
                float half_height = region->height * 0.5f;
                if (region->center.y - half_height > maximum.y ||
                    region->center.y + half_height < minimum.y) continue;
            } else {
                double dx = center->x - region->center.x;
                double dy = center->y - region->center.y;
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
            float dy = region->center.y - center->y;
            float dx = region->center.x - center->x;
            if (radius * radius < dx * dx + dy * dy) continue;
        }
        total += region->value;
        region->accumulated += region->value;
        if (region->limit <= region->accumulated) region->value = 0;
    }
    if (total != 0) {
        data_00474c44 += (total/10+10)/10;
        if (data_00474c44 >= 1000000000) data_00474c44 = 999999999;
    }
    return total;
}
#pragma code_seg()

struct SweepCallerEnemy {
    unsigned char reserved_00[0x2c];
    PickupPoint position;
    unsigned char reserved_34[0xb0 - 0x34];
    PickupPoint size;
};
extern "C" PlayerState* data_00477834;
#pragma code_seg(".text$zz_sweep_caller")
extern "C" __declspec(noinline) int __stdcall PickupSweepCaller(SweepCallerEnemy* enemy) {
    return static_cast<PickupSweepResult*>(0)->Sweep(data_00477834, &enemy->position, &enemy->size);
}
#pragma code_seg()
