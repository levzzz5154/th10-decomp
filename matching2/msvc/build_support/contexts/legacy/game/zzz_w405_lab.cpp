#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef void (__stdcall* LeaveCriticalSectionFn)(void* section);

struct SchedulerTask;
struct FuncCtrl;
extern "C" void __fastcall FuncCtrl_Remove(SchedulerTask* task, FuncCtrl* scheduler);

extern "C" unsigned char g_thread_sync;
extern "C" unsigned char g_scheduler_lock_depth;
extern "C" unsigned char g_func_ctrl;
extern "C" unsigned char g_bomb;

struct RecoveryRawPair {
    unsigned char unknown_00[0x8];
    SchedulerTask* primary;
    SchedulerTask* secondary;
};

void __stdcall LabRecovery(RecoveryRawPair* pair) {
    EnterCriticalSectionFn enter = *(EnterCriticalSectionFn*)&imp_EnterCriticalSection;
    LeaveCriticalSectionFn leave = *(LeaveCriticalSectionFn*)&imp_LeaveCriticalSection;
    FuncCtrl* const scheduler = *(FuncCtrl**)&g_func_ctrl;
    SchedulerTask* task = pair->primary;
    if (task) {
        enter(&g_thread_sync);
        ++g_scheduler_lock_depth;
        FuncCtrl_Remove(task, scheduler);
        leave(&g_thread_sync);
        --g_scheduler_lock_depth;
    }
    task = pair->secondary;
    scheduler = *(FuncCtrl**)&g_func_ctrl;
    if (task) {
        enter(&g_thread_sync);
        ++g_scheduler_lock_depth;
        FuncCtrl_Remove(task, scheduler);
        leave(&g_thread_sync);
        --g_scheduler_lock_depth;
    }
    *(unsigned int*)&g_bomb = 0;
}
