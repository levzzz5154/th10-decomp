// Compiler context only; never selected as recovered game code. The manager's
// destructor and initializer are stand-ins shaped so each takes its receiver
// where the real one does.
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/replay/replay_manager_create_004296f0.cpp"

// C linkage: calls the compiler knows cannot throw, so the stand-in
// destructor needs no unwind state for the node array.
extern "C" void __stdcall ReplayManagerStandIn_Remove(void* scheduler, void* task);
extern "C" int __stdcall ReplayManagerStandIn_Load(char* path);

static __forceinline void ReplayManagerStandIn_Unregister(void* task) {
    void* scheduler = g_func_ctrl;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ReplayManagerStandIn_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// With every callee-saved register busy the receiver stays on the stack.
#pragma code_seg(".text$01dtor")
ReplayManager_004296f0::~ReplayManager_004296f0() {
    void** tasks = reinterpret_cast<void**>(reserved_000);
    ReplayManagerStandIn_Unregister(tasks[2]);
    ReplayManagerStandIn_Unregister(tasks[3]);
}

// The path's address is taken, which keeps it on the stack; the receiver is
// needed after the call and arrives in ESI.
#pragma code_seg(".text$06init")
int ReplayManager_004296f0::Initialize(const char* replay_path) {
    strcpy(path, replay_path);
    if (ReplayManagerStandIn_Load(reinterpret_cast<char*>(&replay_path)))
        return -1;
    return mode;
}

#pragma code_seg(".text$05context")
int __stdcall ReplayManagerCreateCompilerContext(const char* replay_path) {
    return ReplayManager_Create_004296f0(replay_path) != 0;
}
#pragma code_seg()
