// 0x00408210: clear the projectiles inside the manager's region.
#include "th10/game/projectile_manager.hpp"
#include "../../../build_support/layout/ltcg/laser_cut/item_spawn.hpp"
#include "../../../build_support/layout/ltcg/projectile_clear_region/lookup.hpp"

extern "C" {
extern ItemSpawnManager* g_item_manager;
extern unsigned int g_burst_color_small[];  // burst colours of small projectiles
extern unsigned int g_burst_color_medium[];  // ... of medium ones
extern unsigned int g_burst_color_large[];  // ... of large ones
}

#pragma code_seg(".text$f00408210F")
int __stdcall ProjectileManager_ClearRegion(ProjectileManager* manager, int spawn_items) {
    Vec3 high;
    high = manager->region_size * 0.5f;
    Vec3 low;
    low = manager->region_center - high;
    high = high + manager->region_center;

    ProjectileRecord* record = manager->records;
    int remaining = 2000;
    do {
        if (record->state != 0 && record->state != 3) {
            Vec3 record_low, record_high;
            record_low.x = record->position.x - record->size.x * 0.5f;
            record_low.y = record->position.y - record->size.y * 0.5f;
            record_high.x = record->size.x * 0.5f + record->position.x;
            record_high.y = record->size.y * 0.5f + record->position.y;
            if (record_high.x < low.x || record_low.x > high.x ||
                record_high.y < low.y || record_low.y > high.y) {
                continue;
            }
            record->flags |= 8;
            if (spawn_items) {
                g_item_manager->Spawn(reinterpret_cast<const Vector3*>(&record->position), 8, -1,
                                     -1.5707963705062866f, 0.6f);
            }
            Entity* burst = static_cast<AnimationLookup*>(g_sprt_ctrl)->Find(
                static_cast<AnimationLookupContext*>(g_sprt_ctrl),
                reinterpret_cast<CutAnimationResource*>(manager->animations)->CreateOffset(
                    371, reinterpret_cast<const Vector3*>(&record->position)));
            if (record->sprite) {
                if (record->sprite->size <= 16.0f) {
                    burst->primary_color = g_burst_color_small[record->colour];
                } else if (record->sprite->size <= 32.0f) {
                    burst->primary_color = g_burst_color_medium[record->colour];
                } else {
                    burst->primary_color = g_burst_color_large[record->colour];
                }
            }
            record->lifetime = 0;
        }
    } while (++record, --remaining);
    return 0;
}
#pragma code_seg()
