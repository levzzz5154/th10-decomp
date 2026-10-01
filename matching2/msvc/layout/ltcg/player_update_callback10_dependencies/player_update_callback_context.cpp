// Full genuine Update operations; actual native218 context only. Original223 remains unselected ASM.
#include "th10/game/player_update_00405750.hpp"
#pragma code_seg(".text$030update")
int PlayerUpdateState_00405750::Update() {
    if (active_state != 0) {
        switch (active_state) {
        case 1: {
        PositionLookupContext_004492f0* manager=data_00491c10;
        PlayerAnimationValue_00405750* node=reinterpret_cast<PlayerAnimationValue_00405750*>(
            reinterpret_cast<PositionManager_004492f0*>(manager)->Find(manager,animation));
        if (node == 0) {
            animation.value=0;
            active_state=0;
            return 1;
        }
        if ((data_004776f4->flags&1u) &&
            ((data_004776f4->input_state>=0x5D && data_004776f4->input_state<=0x60) ||
              data_004776f4->input_state==0x6D)) {
            position.y-=data_00470b0c;
        } else if (data_00474c68 == 0) {
            position.y-=data_00470afc;
        } else {
            position.y-=data_00470d34;
        }
        PositionVector_004492f0 render={data_00470b4c+position.x,data_00470b48+position.y,position.z};
        SetAnimationPosition_004492f0(&render,manager,animation);
        collision_radius=node->collision_radius;
        Draw();
        break;
    }
        default:
            break;
        }
        timer.Tick();
    }
    return 1;
}
#pragma code_seg()
