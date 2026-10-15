// 0x00405AC0: the bomb's bullet-cancel pass: while the bomb is active, run
// the collision engine over its circle (the last argument depends on the
// player's focus inputs).
#include "th10/game/bomb_state.hpp"
#pragma code_seg(".text$040draw")
int BombState::CancelBullets() {
    if (active_state) {
        if (((g_card->flags & 1u) && g_card->input_state >= 0x5D &&
             g_card->input_state <= 0x60) || g_card->input_state == 0x6D) {
            data_004776f0->Check(&position, collision_radius,
                (~g_card->flags) & 1u, 0);
        } else {
            data_004776f0->Check(&position, collision_radius,
                (~g_card->flags) & 1u, 1);
        }
        g_laser_manager->CopyVectorAndEvaluate(&position.x, collision_radius,
            (~g_card->flags) & 1u);
    }
    return 0;
}
#pragma code_seg()
