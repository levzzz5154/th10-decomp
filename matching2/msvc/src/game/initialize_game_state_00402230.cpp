// Complete state initializer: retail self EAX, stage path ECX, state id on stack.
#include <string.h>
#include <stddef.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "th10/game/scheduler.hpp"
#include "th10/platform/stage_ecl_load_00403850.hpp"
#include "th10/render/camera_batch.hpp"
struct TextLog_0044b8e0 {
    char text[0x2000]; char* cursor; unsigned char dirty;
    __declspec(noinline) char* AppendLine(char* format, ...);
};
struct GameCameraSnapshot_00402230 { RenderCamera camera; char extra[0x118-sizeof(RenderCamera)]; };
struct GameState_00402230 {
    char reserved_000[8]; SchedulerTask* primary; SchedulerTask* secondary;
    char reserved_010[0x38-0x10];
    int timer_previous; int timer_current; float timer_elapsed; const float* timer_speed; unsigned int timer_flags;
    char reserved_04c[0x94-0x4c]; int value_094;
    char reserved_098[0xe0-0x98]; int value_0e0;
    char reserved_0e4[0x1ee0-0xe4]; float frame_limit;
    char reserved_1ee4[0x2a18-0x1ee4]; unsigned int state_flags;
    char reserved_2a1c[0x2a30-0x2a1c]; unsigned int stage_flags; int initialization_frame;
    char reserved_2a38[8]; SchedulerTask* after_draw;
    char reserved_2a44[8]; GameCameraSnapshot_00402230 camera;
};
typedef char GameStateTimerOffsetCheck[offsetof(GameState_00402230,timer_previous)==0x38?1:-1];
typedef char GameStateFrameLimitOffsetCheck[offsetof(GameState_00402230,frame_limit)==0x1ee0?1:-1];
typedef char GameStateFlagsOffsetCheck[offsetof(GameState_00402230,state_flags)==0x2a18?1:-1];
typedef char GameStateAfterDrawOffsetCheck[offsetof(GameState_00402230,after_draw)==0x2a40?1:-1];
typedef char GameCameraSnapshotSizeCheck[sizeof(GameCameraSnapshot_00402230)==0x118?1:-1];
typedef char GameStateCameraOffsetCheck[offsetof(GameState_00402230,camera)==0x2a4c?1:-1];
extern "C" {
extern GameState_00402230* data_004776e4; extern GameState_00402230* data_004776e8;
extern unsigned int data_00474c7c; extern GameCameraSnapshot_00402230 data_00491d7c;
extern Scheduler* data_00491be4; extern float data_00476f78;
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void* callback);
}
#pragma code_seg(".text$01init")
extern "C" __declspec(noinline) int __stdcall InitializeGameState_00402230(GameState_00402230* state, const char* name, int state_id) {
    if (state_id==0) data_004776e8=state; else data_004776e4=state;
    state->stage_flags=data_00474c7c;
    if (((StageEclLoader_00403850*)state)->Load(name)!=0) {
        ((TextLog_0044b8e0*)0x474f70)->AppendLine((char*)0x46cc70);
        return -1;
    }
    state->camera=data_00491d7c;
    state->camera.camera.position=CameraVector(0.0f,0.0f,-600.0f);
    state->camera.camera.direction=CameraVector(0.0f,300.0f,600.0f);
    state->camera.camera.up=CameraVector(0.0f,1.0f,0.0f);
    state->camera.camera.eye_offset=CameraVector(0.0f,0.0f,0.0f);
    state->frame_limit=9610000.0f;
    SchedulerTask* callback=SchedulerCallback_Create_00449ed0((void*)0x403050);
    callback->context=state; callback->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4,callback,state_id+12); state->primary=callback;
    callback=SchedulerCallback_Create_00449ed0((void*)0x403060);
    callback->reserved_flags &= ~1u; callback->context=state;
    Scheduler_RegisterSecondary(data_00491be4,callback,state_id+7); state->secondary=callback;
    callback=SchedulerCallback_Create_00449ed0((void*)0x403070);
    callback->context=state; callback->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4,callback,state_id+10); state->after_draw=callback;
    state->initialization_frame=0;
    // Finish publishing the callback before accessing the embedded timer.
    _ReadWriteBarrier();
    unsigned int timer_flags=state->timer_flags;
    if (!(timer_flags&1)) {
        timer_flags|=1;
        state->timer_current=0;
        state->timer_previous=(int)0xfff0bdc1;
        state->timer_elapsed=0;
        state->timer_speed=&data_00476f78; state->timer_flags=timer_flags;
    }
    // The lazy defaults and the following reset are separate observed writes.
    _ReadWriteBarrier();
    state->timer_current=0; state->timer_elapsed=0; state->timer_previous=-1;
    // Commit the reset before publishing the active-state flag.
    _ReadWriteBarrier();
    state->state_flags|=1; state->value_094=0; state->value_0e0=0;
    return 0;
}
#pragma code_seg()
