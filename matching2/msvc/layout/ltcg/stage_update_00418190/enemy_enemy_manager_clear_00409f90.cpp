#define g_sprt_ctrl stage_enemy_g_sprt_ctrl
#define g_front stage_enemy_g_front
#define data_00474c40 stage_enemy_data_00474c40
#define g_ascii_manager stage_enemy_data_004776e0
#define g_enemy_ctrl stage_enemy_g_enemy_ctrl
#define g_player stage_enemy_data_00477834
#define data_00477838 stage_enemy_data_00477838
#define data_0047783c stage_enemy_data_0047783c
#define data_00476f78 stage_enemy_data_00476f78
#define data_00491fc4 stage_enemy_data_00491fc4
#define data_00491fb8 stage_enemy_data_00491fb8
#define data_00492590 stage_enemy_data_00492590
// 0x00409F90: remove every enemy. Retires the four enemy animation files,
// destroys each enemy in the list, zeroes the counters and lets both manager
// tasks run again. The manager arrives on the stack.
#include "th10/game/enemy_manager_clear_00409f90.hpp"

#pragma code_seg(".text$00409f90_fn")
void EnemyCtrlClearView::Clear() {
    for (int slot = 9; slot < 13; ++slot)
        g_sprt_ctrl->MarkResourceForRemoval(reinterpret_cast<AnimationSlots_00409f90*>(g_sprt_ctrl)->slots[slot]);
    EnemyNode_00409f90* node = first;
    while (node) {
        EnemyNode_00409f90* next = node->next;
        if (node->enemy) node->enemy->Destroy(1);
        node = next;
    }
    spawn_count = 0;
    field_10 = 0;
    if (update_task) update_task->flags &= ~2u;
    if (draw_task) draw_task->flags &= ~2u;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
