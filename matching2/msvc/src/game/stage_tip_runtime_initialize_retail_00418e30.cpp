// 0x00418E30..0x00418EB2 (131 bytes): StageTipRuntime_InitializeRetail
//
// Creates and registers the two scheduler callbacks that drive the stage-tip
// manager, records them on the manager and clears the manager's +0x10 slot.
//
// Retail receives the manager in EBX - a register no MSVC convention assigns -
// and the registration calls keep the callback under construction in ESI with
// the registration priority in EDI, so this source is compiled in the same
// native-LTCG link as the scheduler registration functions it calls (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
//
// The two closing manager stores and the byte read of data_00491D6A are
// volatile.  Without the qualifiers the scheduler hoists `mov al,[data_00491D6A]`
// and the `pop edi` that follows it above the two stores, which is 17 bytes of
// a schedule retail does not have; with them the emitted body is instruction for
// instruction retail's, and the qualifiers add no instruction of their own.
#include "th10/game/scheduler.hpp"

struct RawStageTipManager_00418e30 {
    unsigned char pad_000[0x08];
    void* primary_task_008;              // +0x008, first callback
    void* volatile secondary_task_00C;   // +0x00C, second callback
    void* volatile field_010;            // +0x010
};

extern "C" Scheduler* data_00491be4;
extern "C" volatile unsigned char data_00491d6a;
extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void* callback);
extern "C" int __stdcall asm_FUN_00419960_00419960(
        RawStageTipManager_00418e30* manager, const char* name, int flag);

extern "C" __declspec(noinline) int __stdcall
asm_StageTipRuntime_InitializeRetail_00418e30(RawStageTipManager_00418e30* manager);
#pragma code_seg(".text$00d_dinit")
extern "C" __declspec(noinline) int __stdcall
asm_StageTipRuntime_InitializeRetail_00418e30(RawStageTipManager_00418e30* manager) {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0((void*)0x4198A0);
    primary->context = manager;
    primary->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4, primary, 0x19);
    manager->primary_task_008 = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0((void*)0x4198B0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x2C);
    manager->secondary_task_00C = secondary;
    manager->field_010 = 0;

    if (data_00491d6a) {
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6D8, 0);
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6C4, 1);
    }
    return 0;
}
#pragma code_seg()
