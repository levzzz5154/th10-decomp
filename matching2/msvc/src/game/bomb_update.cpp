// 0x00405750..0x0040582E: Bomb::Update, the per-frame update of the bomb.
//
// An inactive state does nothing.  State 1 follows its animation: when the
// animation is gone the id is forgotten and the state goes inactive without
// ticking; otherwise the state drifts upwards (slower while the focus-style
// inputs 0x5D..0x60 / 0x6D are held, faster when data_00474c68 is set),
// moves the animation to the playfield position, refreshes the collision
// radius from the animation and runs the collision pass.  Every other state
// only ticks the timer.
//
// Three shapes are load-bearing (each measured against the image):
//
//  * The stale id is cleared through a pointer, inside the lookup helper.
//    That store may alias `active_state` as far as the compiler knows, which
//    is what orders retail's two zero stores between the register restores.
//  * The state step is an inlined `void` helper, so a missing animation leaves
//    it with a plain `return` that joins the shared `return 1`.  A separate
//    `return 1` there keeps EBX/EBP saved for the whole function.
//  * SetAnimationPosition takes the context before the position.  The render
//    position pointer (ESI) is then evaluated first, the manager cannot live
//    in ESI, and the shared zero gets ESI with the manager in EBP.
#include "th10/game/bomb_state.hpp"

static inline void* FindAnimationOrClear_00405750(PositionLookupContext_004492f0* manager,
                                                 PositionScriptId_004492f0* id) {
    void* node = reinterpret_cast<PositionManager_004492f0*>(manager)->Find(manager, *id);
    if (node == 0)
        id->value = 0;
    return node;
}

__forceinline void BombState::Step() {
    switch (active_state) {
    case 1: {
        BombAnimationValue* node = static_cast<BombAnimationValue*>(
            FindAnimationOrClear_00405750(data_00491c10, &animation));
        if (node == 0) {
            active_state = 0;
            return;
        }
        if ((data_004776f4->flags & 1u) &&
            ((data_004776f4->input_state >= 0x5D && data_004776f4->input_state <= 0x60) ||
             data_004776f4->input_state == 0x6D)) {
            position.y -= 0.5f;
        } else if (data_00474c68 == 0) {
            position.y -= 1.0f;
        } else {
            position.y -= 1.3f;
        }
        PositionVector_004492f0 render = {position.x + 224.0f, position.y + 16.0f, position.z};
        SetAnimationPosition_004492f0(data_00491c10, &render, animation);
        collision_radius = node->collision_radius;
        CancelBullets();
        break;
    }
    default:
        break;
    }
    timer.Tick();
}

#pragma code_seg(".text$030update")
int BombState::Update() {
    if (active_state != 0)
        Step();
    return 1;
}
#pragma code_seg()
