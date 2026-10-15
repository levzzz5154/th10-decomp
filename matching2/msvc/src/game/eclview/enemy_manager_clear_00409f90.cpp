// 0x00409F90: remove every enemy. Retires the four enemy animation files,
// destroys each enemy in the list, zeroes the counters and lets both manager
// tasks run again. The manager arrives on the stack.
#include "th10/game/enemy_manager_clear_00409f90.hpp"

#pragma code_seg(".text$10clear")
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
