// Compiler context only: this caller is not recovered application code.
#include "../../src/game/effect/effect_initialize.cpp"
#include "th10/game/front_tasks.hpp"

struct Effect;
Effect *Effect_Create();
extern "C" void *__cdecl Bomb_Create(void);
extern "C" int __stdcall asm_Recovery_InstallPairClearFlags_0041ad90(void *pair);
extern "C" void *__cdecl LaserManager_Create(void);
struct ScoreManager_0041c100;
ScoreManager_0041c100 *InitializeManager_0041c100(ScoreManager_0041c100 *manager);

struct RawState_0040a130;
extern "C" int __stdcall EclView_RegisterTasks(RawState_0040a130 *state);

struct EnemyCtrl;
extern "C" int __stdcall EnemyCtrl_Initialize(
        EnemyCtrl *host, int script_name);

// Address-only alias of the independently proven complete genuine zero-argument
// HintCreate419090 entry; pointer in EAX, ordinary cdecl/plainRET.
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

struct Title;
extern "C" int __stdcall Title_RegisterTasks(Title *title);

struct EclViewState;
extern "C" EclViewState *__cdecl asm_FUN_0040a3c0_0040a3c0();

#pragma code_seg(".text$90context")
int __stdcall BulletManagerLoadScriptsCompilerContext(
        FuncCtrl *scheduler, SchedulerTask **tasks, int count, int priority,
        Effect **slots) {
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
        FuncCtrl_RegisterPrimary(scheduler, task, priority);
        FuncCtrl_RegisterSecondary(scheduler, task, priority);
        FuncCtrl_RemoveLocked(scheduler, task);
    }
    FuncCtrl_Remove(scheduler, tasks[0]);
    reinterpret_cast<PublishedBlock*>(slots[0])->Release();
    reinterpret_cast<PublishedBlock*>(slots[1])->Destroy(priority);
    DeletePublishedBlock(reinterpret_cast<PublishedBlock*>(slots[2]));
    int created = 0;
    for (int index = 0; index < count; ++index) {
        slots[index] = Effect_Create();
        if (slots[index])
            ++created;
    }
    if (Bomb_Create())
        ++created;
    if (asm_Recovery_InstallPairClearFlags_0041ad90(tasks[0]))
        ++created;
    for (int index = 0; index < count; ++index) {
        if (LaserManager_Create())
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (InitializeManager_0041c100(
                (ScoreManager_0041c100 *)slots[index]))
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (EnemyCtrl_Initialize(
                (EnemyCtrl *)slots[index], priority) == 0)
            ++created;
    }

    for (int index = 0; index < count; ++index) {
        if (EclView_RegisterTasks((RawState_0040a130 *)slots[index]) == 0)
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (asm_Recovery_CreateResourceState_00419090())
            ++created;
    }
    for (int index = 0; index < count; ++index)
        created += Front_RegisterTasks(
            reinterpret_cast<FrontTaskView*>(slots[index])) == 0;
    for (int index = 0; index < count; ++index)
        created += Title_RegisterTasks(
            reinterpret_cast<Title*>(slots[index])) == 0;
    for (int index = 0; index < count; ++index)
        created += asm_FUN_0040a3c0_0040a3c0() != 0;
    return created;
}
#pragma code_seg()
