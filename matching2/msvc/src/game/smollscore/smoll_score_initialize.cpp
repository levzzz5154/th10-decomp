// 0x0042B4D0: bind the score popups (SmollScore, smollscore.cpp, SmollScoreInf) to the stage animation resource, register
// its update (primary list, priority 0xF) and draw (secondary list, priority
// 0x23) tasks, and set up its sprite from resource entry 0xC4.
// Native LTCG passes the pool in EAX.
#include "th10/game/smoll_score_view.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

struct StageResources_0042b4d0 {
    unsigned char reserved_0000[0x8994];
    Resource_0043e5a0* animation_resource;   // +0x8994
};

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall SmollScoreUpdateTask_0042b9a0(void* pool);
int __fastcall SmollScoreDrawTask_0042b9b0(void* pool);
extern FuncCtrl* g_func_ctrl;
extern StageResources_0042b4d0* g_ascii_manager;
}

#pragma code_seg(".text$00yfn")
int SmollScoreView::Initialize() {
    resource = g_ascii_manager->animation_resource;

    SchedulerTask* task = SchedulerCallback_Create_00449ed0(SmollScoreUpdateTask_0042b9a0);
    task->context = this;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 0xF);
    update_task = task;

    task = SchedulerCallback_Create_00449ed0(SmollScoreDrawTask_0042b9b0);
    task->context = this;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x23);
    draw_task = task;

    Entity* entity = &sprite;
    Resource_0043e5a0* sprite_resource = resource;
    Entity_Init(0, entity);
    entity->script_resource = sprite_resource;
    sprite_resource->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(entity), 0xC4);
    return 0;
}
#pragma code_seg()
