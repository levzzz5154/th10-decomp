#include "collision.hpp"

// 0x00408030: start a live record's vanish.
//
// Only records in state 1 or 2 react. The record moves to state 3; one that
// is still on the playfield spawns its vanish animation and restarts its
// timer, one already more than 8 units outside is just flagged for removal.
// The record arrives in ESI.
#pragma code_seg(".text$c10activate")
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
