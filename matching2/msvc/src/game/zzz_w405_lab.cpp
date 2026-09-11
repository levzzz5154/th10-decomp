#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef void (__stdcall* LeaveCriticalSectionFn)(void* section);

struct SchedulerTask;
struct Scheduler;
extern "C" void __fastcall Scheduler_Remove(SchedulerTask* task, Scheduler* scheduler);

extern "C" unsigned char data_00492274;
extern "C" unsigned char data_0049231c;
extern "C" unsigned char data_00491be4;
extern "C" unsigned char data_004776ec;

struct RecoveryRawPair {
    unsigned char unknown_00[0x8];
    SchedulerTask* primary;
    SchedulerTask* secondary;
};

void __stdcall LabRecovery(RecoveryRawPair* pair) {
    EnterCriticalSectionFn enter = *(EnterCriticalSectionFn*)&data_004660b0;
    LeaveCriticalSectionFn leave = *(LeaveCriticalSectionFn*)&data_004660b4;
    Scheduler* const scheduler = *(Scheduler**)&data_00491be4;
    SchedulerTask* task = pair->primary;
    if (task) {
        enter(&data_00492274);
        ++data_0049231c;
        Scheduler_Remove(task, scheduler);
        leave(&data_00492274);
        --data_0049231c;
    }
    task = pair->secondary;
    scheduler = *(Scheduler**)&data_00491be4;
    if (task) {
        enter(&data_00492274);
        ++data_0049231c;
        Scheduler_Remove(task, scheduler);
        leave(&data_00492274);
        --data_0049231c;
    }
    *(unsigned int*)&data_004776ec = 0;
}
