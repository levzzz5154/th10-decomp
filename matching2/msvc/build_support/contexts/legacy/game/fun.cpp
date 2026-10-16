#include "th10/game/player_update_collision.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct CollisionDisplacement : PositionVector {
    CollisionDisplacement(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }
};

#pragma code_seg(".text$060collision")
int CollisionEngine::Check(const PositionVector* point,
        float radius, int spawn_item, int filter_countdown) {
    CollisionRecord* record = records;
    int remaining = 2000;
    do {
        if (record->state != 0 && record->state != 3 &&
                (!filter_countdown || !record->countdown)) {
            // Materialize all three displacement components before evaluating
            // the X/Y circle. Retail retains the Z subtraction and each of
            // the three vector-copy operations.
            PositionVector displacement = CollisionDisplacement(
                record->position.x - point->x,
                record->position.y - point->y,
                record->position.z - point->z);
            float diameter = record->collision_diameter;
            // Preserve the original field read before the shared scale read.
            _ReadWriteBarrier();
            float combined_radius = diameter * flt_0_5 + radius;
            float distance_squared = displacement.x * displacement.x +
                displacement.y * displacement.y;
            // FCOMPP/TEST AH,5/JNP skips an ordered radius below distance.
            // The unordered comparison follows the collision path as well.
            if (!(distance_squared > combined_radius * combined_radius)) {
                record->Activate();
                const PlayfieldPoint* location =
                    reinterpret_cast<const PlayfieldPoint*>(&record->position);
                if (!location->OutsideBounds(2.0f, 2.0f) && spawn_item) {
                    g_item_manager->Spawn(&record->position.x, 8, -1,
                        -1.5707963705062866f, 0.6000000238418579f);
                }
            }
        }
        ++record;
    } while (--remaining);
    return 0;
}
#pragma code_seg()
