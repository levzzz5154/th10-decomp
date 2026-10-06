#include "runtime.hpp"
#include <math.h>
#pragma intrinsic(sin,cos)

#pragma code_seg(".text$20sweep")
int PickupSweepResult::Sweep(PickupManager* manager, const PickupPoint* center,
                            const PickupPoint* size) {
    int total=0;
    if (manager->generation_end == manager->generation_begin) return 0;
    float half_x = size->x * 0.5f, half_y = size->y * 0.5f;
    PickupPosition minimum;
    minimum.x=center->x-half_x; minimum.y=center->y-half_y;
    PickupPosition maximum;
    maximum.x=center->x+half_x; maximum.y=center->y+half_y;
    if (this) value = 0;
    PickupRecord* pickup = manager->pickups;
    // Retail reuses this maximum corner for the rotated region point.
    PickupPosition working_point;
    for (int count = 128; count != 0; --count, ++pickup) {
        if (pickup->state == 0 || pickup->state == 2) continue;
        PickupDescriptor* descriptor = pickup->descriptor;
        double width = descriptor->width * 0.5f;
        // Retail stores these three edges as binary32 before comparing them.
        // Maximum Y stays in x87 precision until its lower-bound comparison.
        volatile PickupPosition pickup_minimum;
        pickup_minimum.x=static_cast<float>(pickup->position.x-width);
        double height = descriptor->height * 0.5f;
        pickup_minimum.y=static_cast<float>(pickup->position.y-height);
        volatile float& rounded_right=working_point.x;
        rounded_right=static_cast<float>(pickup->position.x+width);
        // This ordinary member stays extended in the measured native body.
        working_point.y=static_cast<float>(pickup->position.y+height);
        if (pickup_minimum.y > maximum.y || pickup_minimum.x > maximum.x || working_point.y < minimum.y || rounded_right < minimum.x)
            continue;
        if (descriptor->type != 3) {
            if (pickup_minimum.y < 0.0f) continue;
        } else if (maximum.y < 0.0f) continue;
        if (descriptor->filter && descriptor->filter(manager,pickup,center)) continue;
        if (!pickup->initialized) {
            pickup->handle.StopAtFrame2();
            pickup->initialized = 1;
        }
        descriptor = pickup->descriptor;
        pickup->collected = 1;
        unsigned char type = descriptor->type;
        if (type != 3 || pickup->clock.AtInterval(4)) total += descriptor->value;
        if (type != 3) {
            float saved_angle = pickup->handle.Validate()->angle;
            pickup->handle.Retire();
            descriptor = pickup->descriptor;
            PickupHandle created;
            pickup->handle = *Pickup_CreatePrimaryBack(manager->animation_resource,&created,
                                                       descriptor->collected_script+5,15);
            PickupAnimation* object = pickup->handle.Validate();
            object->angle = saved_angle;
            object->flags |= 4u;
            pickup->position.z = 0.1f;
            pickup->state = 2;
            pickup->velocity_scale *= 0.125f;
        }
        descriptor = pickup->descriptor;
        if (descriptor->type == 2) {
            int indicator_value = descriptor->value/3;
            Pickup_AllocateIndicator(descriptor->value,manager,&pickup->position,
                                     0x42000000u,0x3fb33333u,13,indicator_value);
        }
    }
    total += data_004776ec->HitTest(center);
    PickupRegion* region = manager->regions;
    for (int count = 32; count != 0; --count, ++region) {
        if (!(region->flags & 1u)) continue;
        if (region->timer.current != region->timer.previous &&
            region->timer.current % region->interval == 0) continue;
        if (region->flags & 2u) {
            double dy = static_cast<double>(region->center.y)-center->y;
            double dx = static_cast<double>(region->center.x)-center->x;
            if (static_cast<double>(region->radius)*region->radius < dx*dx+dy*dy) continue;
        } else if (region->angle == 0.0f) {
            double width = region->width*0.5f;
            if (region->center.x-width > maximum.x || region->center.x+width < minimum.x) continue;
            double height = region->height*0.5f;
            if (region->center.y-height > maximum.y || region->center.y+height < minimum.y) continue;
        } else {
            double dx = static_cast<double>(center->x)-region->center.x;
            double dy = static_cast<double>(center->y)-region->center.y;
            float sine = static_cast<float>(sin(-region->angle));
            double cosine = cos(-region->angle);
            volatile float& rotated_x=working_point.x;
            volatile float& rotated_y=working_point.y;
            rotated_x = static_cast<float>(cosine*dx-sine*dy);
            rotated_y = static_cast<float>(sine*dx+cosine*dy);
            double hx = size->x*0.5f;
            if (rotated_x+hx < region->width*-0.5f || rotated_x-hx > region->width*0.5f) continue;
            double hy = size->y*0.5f;
            if (rotated_y+hy < region->height*-0.5f || rotated_y-hy > region->height*0.5f) continue;
        }
        int contribution = region->value;
        total += contribution;
        region->accumulated += contribution;
        if (region->accumulated >= region->limit) region->value = 0;
    }
    if (total != 0) {
        data_00474c44 += (total/10+10)/10;
        if (data_00474c44 >= 1000000000) data_00474c44 = 999999999;
    }
    return total;
}
#pragma code_seg()
