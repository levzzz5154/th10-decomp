#include "../../../build_support/layout/ltcg/player_state_collision_runtime/collision.hpp"

// 0x00408030: start a live record's vanish.
//
// Only records in state 1 or 2 react. The record moves to state 3; one that
// is still on the playfield spawns its vanish animation and restarts its
// timer, one already more than 8 units outside is just flagged for removal.
// The record arrives in ESI.
#pragma code_seg(".text$f00408030F")
int PlayerCollisionRecord::Activate() {
    if (state != 2 && state != 1) return 0;
    if (!reinterpret_cast<const PlayfieldPoint*>(&position)->OutsideBounds(8.0f, 8.0f)) {
        state = 3;
        animation_state = 1;
        if (animation_index >= 0) {
            static_cast<AnimationResource_0043e710*>(data_004776f0->item_animation)->
                CreateOffset(animation_index, reinterpret_cast<const Vector3*>(&position));
        }
        if (!(timer_flags & 1u)) {
            timer_current = 0;
            timer_previous = -999999;
            timer_elapsed = 0.0f;
            timer_speed = &data_00476f78;
            timer_flags |= 1u;
        }
        timer_current = 0;
        timer_elapsed = 0.0f;
        timer_previous = -1;
        return 1;
    }
    state = 3;
    animation_state = 1;
    flags |= 8;
    return 1;
}
#pragma code_seg()

#include "../../../build_support/layout/ltcg/player_state_collision_runtime/item_spawn.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct CollisionDisplacement_00408100 : Vec3 {
    CollisionDisplacement_00408100(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }
};

#pragma code_seg(".text$f00408100F")
int PlayerCollisionEngine::Check(const Vec3* point,
        float radius, int spawn_item, int filter_countdown) {
    PlayerCollisionRecord* record = records;
    int remaining = 2000;
    do {
        if (record->state != 0 && record->state != 3 &&
                (!filter_countdown || !record->countdown)) {
            // Materialize all three displacement components before evaluating
            // the X/Y circle. Retail retains the Z subtraction and each of
            // the three vector-copy operations.
            Vec3 displacement = CollisionDisplacement_00408100(
                record->position.x - point->x,
                record->position.y - point->y,
                record->position.z - point->z);
            float diameter = record->collision_diameter;
            // Preserve the original field read before the shared scale read.
            _ReadWriteBarrier();
            float combined_radius = diameter * data_00470b0c + radius;
            float distance_squared = displacement.x * displacement.x +
                displacement.y * displacement.y;
            // FCOMPP/TEST AH,5/JNP skips an ordered radius below distance.
            // The unordered comparison follows the collision path as well.
            if (!(distance_squared > combined_radius * combined_radius)) {
                record->Activate();
                const PlayfieldPoint* location =
                    reinterpret_cast<const PlayfieldPoint*>(&record->position);
                if (!location->OutsideBounds(2.0f, 2.0f) && spawn_item) {
                    data_00477818->Spawn(reinterpret_cast<const Vector3*>(&record->position), 8, -1,
                        -1.5707963705062866f, 0.6000000238418579f);
                }
            }
        }
        ++record;
    } while (--remaining);
    return 0;
}
#pragma code_seg()
