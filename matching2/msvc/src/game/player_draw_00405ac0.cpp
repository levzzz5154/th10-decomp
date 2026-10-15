#include "th10/game/player_update_00405750.hpp"
#pragma code_seg(".text$040draw")
int PlayerUpdateState_00405750::Draw() {
    if (active_state) {
        if (((data_004776f4->flags & 1u) && data_004776f4->input_state >= 0x5D &&
             data_004776f4->input_state <= 0x60) || data_004776f4->input_state == 0x6D) {
            data_004776f0->Check(&position, collision_radius,
                (~data_004776f4->flags) & 1u, 0);
        } else {
            data_004776f0->Check(&position, collision_radius,
                (~data_004776f4->flags) & 1u, 1);
        }
        g_laser_manager->CopyVectorAndEvaluate(&position.x, collision_radius,
            (~data_004776f4->flags) & 1u);
    }
    return 0;
}
#pragma code_seg()
