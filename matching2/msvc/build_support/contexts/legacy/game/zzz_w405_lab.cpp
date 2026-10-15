#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef void (__stdcall* LeaveCriticalSectionFn)(void* section);

struct SchedulerTask;
struct FuncCtrl;
extern "C" void __fastcall FuncCtrl_Remove(SchedulerTask* task, FuncCtrl* scheduler);

extern "C" unsigned char data_00492274;
extern "C" unsigned char data_0049231c;
extern "C" unsigned char g_func_ctrl;
extern "C" unsigned char g_bomb;

struct RecoveryRawPair {
    unsigned char unknown_00[0x8];
    SchedulerTask* primary;
    SchedulerTask* secondary;
};

void __stdcall LabRecovery(RecoveryRawPair* pair) {
    EnterCriticalSectionFn enter = *(EnterCriticalSectionFn*)&data_004660b0;
    LeaveCriticalSectionFn leave = *(LeaveCriticalSectionFn*)&data_004660b4;
    FuncCtrl* const scheduler = *(FuncCtrl**)&g_func_ctrl;
    SchedulerTask* task = pair->primary;
    if (task) {
        enter(&data_00492274);
        ++data_0049231c;
        FuncCtrl_Remove(task, scheduler);
        leave(&data_00492274);
        --data_0049231c;
    }
    task = pair->secondary;
    scheduler = *(FuncCtrl**)&g_func_ctrl;
    if (task) {
        enter(&data_00492274);
        ++data_0049231c;
        FuncCtrl_Remove(task, scheduler);
        leave(&data_00492274);
        --data_0049231c;
    }
    *(unsigned int*)&g_bomb = 0;
}
