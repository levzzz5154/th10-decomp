// Compiler context only; never selected as recovered game code. The manager's
// destructor and initializer are stand-ins shaped so each takes its receiver
// where the real one does.
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/stage_manager_create_004296f0.cpp"

extern "C" void* data_00491be4;
// C linkage: calls the compiler knows cannot throw, so the stand-in
// destructor needs no unwind state for the node array.
extern "C" void __stdcall StageManagerStandIn_Remove(void* scheduler, void* task);
extern "C" int __stdcall StageManagerStandIn_Load(char* path);

static __forceinline void StageManagerStandIn_Unregister(void* task) {
    void* scheduler = data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        StageManagerStandIn_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

// With every callee-saved register busy the receiver stays on the stack.
#pragma code_seg(".text$01dtor")
StageManager_004296f0::~StageManager_004296f0() {
    void** tasks = reinterpret_cast<void**>(reserved_000);
    StageManagerStandIn_Unregister(tasks[2]);
    StageManagerStandIn_Unregister(tasks[3]);
}

// The path's address is taken, which keeps it on the stack; the receiver is
// needed after the call and arrives in ESI.
#pragma code_seg(".text$06init")
int StageManager_004296f0::Initialize(const char* stage_path) {
    strcpy(path, stage_path);
    if (StageManagerStandIn_Load(reinterpret_cast<char*>(&stage_path)))
        return -1;
    return mode;
}

#pragma code_seg(".text$05context")
int __stdcall StageManagerCreateCompilerContext(const char* stage_path) {
    return StageManager_Create_004296f0(stage_path) != 0;
}
#pragma code_seg()
