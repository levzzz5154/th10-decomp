// Compiler context only; never selected as recovered game code. The real
// initializer is compiled here for its private convention. The constructor
// and destructor are stand-ins without unwind tables of their own, shaped so
// each takes its receiver on the stack as the real ones do.
#define TH10_GAME_STATE_LAYOUT_ONLY
#include "../../src/game/initialize_game_state_00402230.cpp"
#include "th10/platform/thread_sync.hpp"

void __cdecl operator delete(void* block);
#pragma code_seg(".text$13remove")
extern "C" __declspec(noinline) void __stdcall Scheduler_Remove(Scheduler* scheduler, SchedulerTask* task) {
    if (!task) return;
    TaskLink* node = &scheduler->primary.link;
    while (node) {
        if (node->task == task) break;
        node = node->next;
    }
    if (!node) {
        node = &scheduler->secondary.link;
        while (node) {
            if (node->task == task) break;
            node = node->next;
        }
    }
    if (node && node->previous) {
        node->Unlink();
        task->on_tick = 0;
        if (task->heap_owned) delete task;
    }
}
#pragma code_seg()

// C++ linkage: a call the compiler must assume can throw.
void __stdcall GameStateStandIn_MayThrow(void* state);

// With every callee-saved register busy the receiver stays on the stack.
static __forceinline void GameStateStandIn_Unregister(GameState_00402230* state) {
    SchedulerTask* task = state->primary;
    Scheduler* scheduler = data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = state->secondary;
    scheduler = data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

#pragma code_seg(".text$02dtor")
GameState_00402230::~GameState_00402230() {
    GameStateStandIn_Unregister(this);
}
#pragma code_seg()

// A call that may throw gives the factory its cleanup state.
#pragma code_seg(".text$01ctor")
GameState_00402230::GameState_00402230() {
    GameStateStandIn_Unregister(this);
    GameStateStandIn_MayThrow(0);
}
#pragma code_seg()

#include "../../src/game/create_game_state_00402640.cpp"

#pragma code_seg(".text$17context")
extern "C" GameState_00402230* __stdcall CreateGameStateContext_00402640(const char* name, int state_id) { return CreateGameState_00402640(name, state_id); }
#pragma code_seg()
