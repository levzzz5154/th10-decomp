#define data_00491c10 stage_enemy_data_00491c10
#define data_0047770c stage_enemy_data_0047770c
#define data_00474c40 stage_enemy_data_00474c40
#define g_ascii_manager stage_enemy_data_004776e0
#define data_00477704 stage_enemy_data_00477704
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
void EnemyManager_00409f90::Clear() {
    for (int slot = 9; slot < 13; ++slot)
        data_00491c10->MarkResourceForRemoval(reinterpret_cast<AnimationSlots_00409f90*>(data_00491c10)->slots[slot]);
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
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
