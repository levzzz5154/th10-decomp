// 0x0042B4D0: bind the score popups (SmollScore, smollscore.cpp, SmollScoreInf) to the stage animation resource, register
// its update (primary list, priority 0xF) and draw (secondary list, priority
// 0x23) tasks, and set up its sprite from resource entry 0xC4.
// Native LTCG passes the pool in EAX.
#include "th10/game/smoll_score_view.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/render/animation_object.hpp"

struct StageResources2 {
    unsigned char reserved_0000[0x8994];
    Resource2* animation_resource;   // +0x8994
};

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall SmollScoreUpdateTask(void* pool);
int __fastcall SmollScoreDrawTask(void* pool);
extern FuncCtrl* g_func_ctrl;
extern StageResources2* g_ascii_manager;
}

#pragma code_seg(".text$00yfn")
int SmollScoreView::Initialize() {
    resource = g_ascii_manager->animation_resource;

    SchedulerTask* task = SchedulerTask_Create(SmollScoreUpdateTask);
    task->context = this;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 0xF);
    update_task = task;

    task = SchedulerTask_Create(SmollScoreDrawTask);
    task->context = this;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x23);
    draw_task = task;

    Entity* entity = &sprite;
    Resource2* sprite_resource = resource;
    Entity_Init(0, entity);
    entity->script_resource = sprite_resource;
    sprite_resource->ConfigureObject(reinterpret_cast<AnimationObject3*>(entity), 0xC4);
    return 0;
}
#pragma code_seg()
