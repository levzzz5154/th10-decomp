// 0x0042B4D0: bind the effect pool to the stage animation resource, register
// its update (primary list, priority 0xF) and draw (secondary list, priority
// 0x23) tasks, and set up its sprite from resource entry 0xC4.
// Native LTCG passes the pool in EAX.
#include "th10/game/effect_pool_0042b6f0.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

struct StageResources_0042b4d0 {
    unsigned char reserved_0000[0x8994];
    Resource_0043e5a0* animation_resource;   // +0x8994
};

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall EffectPoolUpdate_0042b9a0(void* pool);
int __fastcall EffectPoolDraw_0042b9b0(void* pool);
extern Scheduler* data_00491be4;
extern StageResources_0042b4d0* g_ascii_manager;
}

#pragma code_seg(".text$00yfn")
int EffectPool_0042b6f0::Initialize() {
    resource = g_ascii_manager->animation_resource;

    SchedulerTask* task = SchedulerCallback_Create_00449ed0(EffectPoolUpdate_0042b9a0);
    task->context = this;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4, task, 0xF);
    update_task = task;

    task = SchedulerCallback_Create_00449ed0(EffectPoolDraw_0042b9b0);
    task->context = this;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x23);
    draw_task = task;

    Entity* entity = &sprite;
    Resource_0043e5a0* sprite_resource = resource;
    Entity_Init(0, entity);
    entity->script_resource = sprite_resource;
    sprite_resource->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(entity), 0xC4);
    return 0;
}
#pragma code_seg()
