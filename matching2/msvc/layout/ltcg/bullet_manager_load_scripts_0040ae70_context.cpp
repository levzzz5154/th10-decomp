// Compiler context only: this caller is not recovered application code.
#include "../../src/game/bullet_manager_load_scripts_0040ae70.cpp"
#include "th10/game/item_front_initialize_00413980.hpp"

struct BulletManagerState_0040af90;
BulletManagerState_0040af90 *BulletManager_Create_0040af90();
extern "C" void *__cdecl asm_Recovery_CreateFixedState_004056b0(void);
extern "C" int __stdcall asm_Recovery_InstallPairClearFlags_0041ad90(void *pair);
extern "C" void *__cdecl asm_ScoreManager_CreateAndInitRetail_0041c290(void);
struct ScoreManager_0041c100;
ScoreManager_0041c100 *InitializeManager_0041c100(ScoreManager_0041c100 *manager);

struct RawState_0040a130;
extern "C" int __stdcall asm_FUN_0040a130_0040a130(RawState_0040a130 *state);

struct RawStageTipManager_00418e30;
extern "C" int __stdcall asm_StageTipRuntime_InitializeRetail_00418e30(
        RawStageTipManager_00418e30 *manager);

struct MessageHost_0040d280;
extern "C" int __stdcall asm_MessageHost_InitRetail_0040d280(
        MessageHost_0040d280 *host, int script_name);

extern "C" void* __cdecl asm_Recovery_CreateResourceState_00419090();
struct SchedulerCreatePrimary_0044A000 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
struct SchedulerCreateSecondary_0044A030 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
struct SchedulerCreatePrimaryClear_0044a060 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
struct SchedulerCreateSecondaryClear_0044a090 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};


struct PublishedBlock {
    __declspec(noinline) void Release();
    __declspec(noinline) PublishedBlock* Destroy(unsigned int flags);
};
__declspec(noinline) void DeletePublishedBlock(PublishedBlock* block);

struct TitleState_0042caa0;
extern "C" int __stdcall Title_RegisterTasks_0042caa0(TitleState_0042caa0 *title);

#pragma code_seg(".text$90context")
int __stdcall BulletManagerLoadScriptsCompilerContext(
        Scheduler *scheduler, SchedulerTask **tasks, int count, int priority,
        BulletManagerState_0040af90 **slots) {
    for (int index = 0; index < count; ++index) {
        SchedulerCreatePrimary_0044A000 *primary =
            (SchedulerCreatePrimary_0044A000 *)tasks[index];
        primary->Create(slots[index], priority);
        SchedulerCreateSecondary_0044A030 *secondary =
            (SchedulerCreateSecondary_0044A030 *)tasks[index];
        secondary->Create(slots[index], priority);
        ((SchedulerCreatePrimaryClear_0044a060 *)tasks[index])->Create(slots[index], priority);
        ((SchedulerCreateSecondaryClear_0044a090 *)tasks[index])->Create(slots[index], priority);
    }
    for (int index = 0; index < count; ++index) {
        SchedulerTask *task = tasks[index];
        Scheduler_RegisterPrimary(scheduler, task, priority);
        Scheduler_RegisterSecondary(scheduler, task, priority);
        Scheduler_RemoveLocked(scheduler, task);
    }
    Scheduler_Remove(scheduler, tasks[0]);
    reinterpret_cast<PublishedBlock*>(slots[0])->Release();
    reinterpret_cast<PublishedBlock*>(slots[1])->Destroy(priority);
    DeletePublishedBlock(reinterpret_cast<PublishedBlock*>(slots[2]));
    int created = 0;
    for (int index = 0; index < count; ++index) {
        slots[index] = BulletManager_Create_0040af90();
        if (slots[index])
            ++created;
    }
    if (asm_Recovery_CreateFixedState_004056b0())
        ++created;
    if (asm_Recovery_InstallPairClearFlags_0041ad90(tasks[0]))
        ++created;
    for (int index = 0; index < count; ++index) {
        if (asm_ScoreManager_CreateAndInitRetail_0041c290())
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (InitializeManager_0041c100(
                (ScoreManager_0041c100 *)slots[index]))
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (asm_StageTipRuntime_InitializeRetail_00418e30(
                (RawStageTipManager_00418e30 *)slots[index]) == 0)
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (asm_MessageHost_InitRetail_0040d280(
                (MessageHost_0040d280 *)slots[index], priority) == 0)
            ++created;
    }

    for (int index = 0; index < count; ++index) {
        if (asm_FUN_0040a130_0040a130((RawState_0040a130 *)slots[index]) == 0)
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (asm_Recovery_CreateResourceState_00419090())
            ++created;
    }
    for (int index = 0; index < count; ++index)
        created += ItemFront_Initialize_00413980(
            reinterpret_cast<ItemFrontState_00413980*>(slots[index])) == 0;
    for (int index = 0; index < count; ++index)
        created += Title_RegisterTasks_0042caa0(
            reinterpret_cast<TitleState_0042caa0*>(slots[index])) == 0;
    return created;
}
#pragma code_seg()
