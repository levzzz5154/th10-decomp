// Readable models removed from matching2/msvc/src/game/bullet.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include "asm_encoding.hpp"
#include "th10/platform/thread_sync.hpp"
#include "asm_symbols.hpp"
#include <string.h>
#include "th10/game/entity.hpp"

extern "C" CriticalSection data_00492274;

// 0x0040AF00..0x0040AF88: ?BulletManager_Release@@
// Ghidra shows a one-pointer stack argument with callee cleanup (ret 4).
struct BulletManagerReleaseState_0040af00 {
    unsigned int unknown_00;
    unsigned int unknown_04;
    void* scheduler_task_at_08;
    void* scheduler_task_at_0c;
};

typedef void (__stdcall *BulletManagerCriticalSectionFn_0040af00)(void* section);

extern "C" void __fastcall Scheduler_Remove(void* task, void* scheduler);

extern "C" void __stdcall asm_BulletManager_Release_0040af00(
        BulletManagerReleaseState_0040af00* state) {
    BulletManagerCriticalSectionFn_0040af00 enter_critical_section =
        *(BulletManagerCriticalSectionFn_0040af00*)&data_004660b0;
    BulletManagerCriticalSectionFn_0040af00 leave_critical_section =
        *(BulletManagerCriticalSectionFn_0040af00*)&data_004660b4;
    void* const first_task = state->scheduler_task_at_08;
    void* scheduler = *(void**)&data_00491be4;

    if (first_task != 0) {
        enter_critical_section(&data_00492274);
        ++data_0049231c;
        Scheduler_Remove(first_task, scheduler);
        leave_critical_section(&data_00492274);
        --data_0049231c;
    }

    void* const second_task = state->scheduler_task_at_0c;
    scheduler = *(void**)&data_00491be4;
    if (second_task != 0) {
        enter_critical_section(&data_00492274);
        ++data_0049231c;
        Scheduler_Remove(second_task, scheduler);
        leave_critical_section(&data_00492274);
        --data_0049231c;
    }

    *(void**)&data_004776fc = 0;
}
