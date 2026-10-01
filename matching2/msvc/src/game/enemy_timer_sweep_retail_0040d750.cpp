// 0x0040D750: update every listed enemy, retiring the finished and flagged
// ones, then advance the manager's frame timer. Native LTCG keeps the manager
// in EDI.
// 0x0040D810: the scheduler callback, which forwards its ECX context.
#include "th10/game/enemy_timer_sweep_0040d750.hpp"

#pragma code_seg(".text$01sweep")
int EnemyTimerSweepManager_0040d750::Sweep() {
    EnemyTimerSweepLink_0040d750* next;
    for (EnemyTimerSweepLink_0040d750* link = enemy_list_head_058; link; link = next) {
        next = link->next;
        if (!(link->owner->flags_2480 & 0x20000) && !EnemyUpdate_0040dc80(link->owner->update_context_103c)) {
            link->owner->flags_2480 &= ~0x400;
        } else if (link->owner) {
            link->owner->RetireFromSweep(1);
        }
    }
    frame_040.Tick();
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$02task")
int __fastcall EnemyTimerSweep_Task_0040d810(EnemyTimerSweepManager_0040d750* manager) {
    return manager->Sweep();
}
#pragma code_seg()
