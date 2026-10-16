// Compiler context only; never compared as recovered game code. Compiled
// beside the equivalent replay bootstrap body so the whole-program /LTCG pass
// derives the register conventions retail uses at its edges: the factory at
// 0x00429610 homes the bootstrap's receiver in EBX with the mode in EAX and
// the path in ECX, and the loader, pool, timer, configuration and scheduler
// helpers keep the private conventions their retail callers use. The
// bootstrap's own Start definition is NOT here; the model supplies it.
#include <string.h>
#include <stdlib.h>
#include "th10/core/func_ctrl.hpp"
#include "th10/game/linked_pool_append.hpp"
#include "th10/game/large_initialization_state.hpp"
#include "th10/platform/thread_sync.hpp"
#include "../../../src/game/replay/replay_manager_create_00429610.cpp"

// C linkage: calls the compiler knows cannot throw, so the stand-in
// destructor needs no unwind state for the node array.
extern "C" void __stdcall ReplayManagerStandIn_Remove(void* scheduler, void* task);
extern "C" int __stdcall ReplayManagerStandIn_Load(const char* path);
extern "C" char g_key_bindings_current[];
extern "C" float g_game_speed;

// Same shape the equivalent body declares; the member definition lands here.
struct EmbeddedTimerState {
    unsigned char unknown_00[0x14];
    int target_14;
    int current_18;
    float previous_1c;
    float* speed_20;
    unsigned int flags_24;

    __declspec(noinline) void SetCountdown(int frames);
};

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
ReplayManager::~ReplayManager() {
    void** tasks = reinterpret_cast<void**>(reserved_000);
    ReplayManagerStandIn_Unregister(tasks[2]);
    ReplayManagerStandIn_Unregister(tasks[3]);
}

// The path's address is taken, which keeps it on the stack; the receiver is
// needed after the call and arrives in ESI, like the real loader's.
__declspec(noinline) int ReplayManager_LoadFile2(
        ReplayManager* manager, const char* replay_path) {
    strcpy(manager->path, replay_path);
    if (ReplayManagerStandIn_Load((const char*)&replay_path))
        return -1;
    return manager->mode;
}

// The frame countdown timer; the receiver is the containing score-state
// object and arrives in EAX at the retail call site.
void EmbeddedTimerState::SetCountdown(int frames) {
    if ((this->flags_24 & 1) == 0) {
        this->current_18 = 0;
        this->target_14 = 0xFFF0BDC1;
        this->previous_1c = 0.0f;
        this->speed_20 = &g_game_speed;
        this->flags_24 |= 1;
    }
    this->current_18 = frames;
    this->target_14 = frames - 1;
    this->previous_1c = (float)frames;
}

// The pool page append; the slot arrives in ESI and the owner is pushed.
PoolLink* PoolOwner::AppendPage(int slot) {
    PoolLink* link = &(new PoolPage)->link;
    PoolLink* tail = &lists[slot];
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        link->next = tail->next;
        tail->next->previous = link;
    }
    tail->next = link;
    link->previous = tail;
    return link;
}

// Complete list release; the stage arrives in EAX and the lists in ECX.
extern "C" __declspec(noinline) void __stdcall
ReplayPool_Clear(ReplayPoolLists* lists, int stage) {
    ReplayPoolLink2* current = lists->stages[stage].next;
    while (current) {
        ReplayPoolLink2* next = current->next;
        ReplayPool* pool = current->pool;
        if (pool) {
            if (pool->link.next) pool->link.next->previous = pool->link.previous;
            if (pool->link.previous) pool->link.previous->next = pool->link.next;
            pool->link.next = 0;
            pool->link.previous = 0;
            free(pool);
        }
        current = next;
    }
}

// The game-configuration defaults; the block pointer is the only live
// argument and lands in EDX, with the unused fastcall slot never loaded.
char __fastcall GameConfig_InitializeDefaults(int unused, GameConfig* config) {
    memset(config, 0, 0x34);
    config->field_1a = 0;
    config->version_marker = 0x100003;
    config->field_1d = 0;
    config->field_1e = 0;
    config->window_width = 0x258;
    config->window_height = 0x258;
    config->field_1b = 1;
    config->field_1c = 1;
    config->flags |= 0x100;
    memcpy(config->version_prefix, g_key_bindings_current, 18);
    config->field_1f = 2;
    config->field_22 = 0;
    config->field_20 = 100;
    config->field_21 = 0x50;
    return 0;
}

// The task arrives in ESI and its priority in EDI; only the scheduler is
// pushed, exactly as at the bootstrap's retail call sites.
extern "C" __declspec(noinline) int __stdcall FuncCtrl_RegisterPrimary(
        FuncCtrl* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->primary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}

extern "C" __declspec(noinline) int __stdcall FuncCtrl_RegisterSecondary(
        FuncCtrl* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->secondary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}

#pragma code_seg(".text$05context")
int __stdcall ReplayManagerStartCompilerContext(int start_mode, const char* replay_path) {
    return ReplayManager_Create2(start_mode, replay_path) != 0;
}
#pragma code_seg()
