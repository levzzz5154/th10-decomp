// Compiler context only; never selected as recovered game code. The display
// constructor is a stand-in shaped to take its receiver and its argument on
// the stack as the real one does.
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/front/item_score_display_create_00415db0.cpp"

extern "C" void* g_func_ctrl;
extern "C" void __stdcall ScoreDisplayStandIn_Remove(void* scheduler, void* task);
// C++ linkage: a call the compiler must assume can throw.
void __stdcall ScoreDisplayStandIn_MayThrow(void* argument);

static __forceinline void ScoreDisplayStandIn_Unregister(void* task) {
    void* scheduler = g_func_ctrl;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ScoreDisplayStandIn_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// With every callee-saved register busy the receiver stays on the stack;
// taking the argument's address keeps it there too.
#pragma code_seg(".text$01a_ctor")
ItemScoreDisplay_00415db0::ItemScoreDisplay_00415db0(void* script) {
    void** tasks = reinterpret_cast<void**>(reserved_04);
    ScoreDisplayStandIn_Unregister(tasks[1]);
    ScoreDisplayStandIn_Unregister(tasks[2]);
    ScoreDisplayStandIn_MayThrow(&script);
}

// Elsewhere the program takes the next stage's address, so a store through a
// pointer may change it.
extern "C" void __stdcall ScoreDisplayStandIn_Publish(int* next_stage);

#pragma code_seg(".text$01c_context")
int __stdcall ItemScoreDisplayCompilerContext(ItemManager_00415db0** managers, int* stages, int count) {
    ScoreDisplayStandIn_Publish(&data_00474c84);
    for (int i = 0; i < count; ++i)
        managers[i]->CreateScoreDisplay(stages[i]);
    return count;
}
#pragma code_seg()
