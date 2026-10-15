// Complete state initializer: retail self EAX, stage path ECX, state id on stack.
#include <string.h>
#include <stddef.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "th10/core/func_ctrl.hpp"
#include "th10/render/camera_batch.hpp"
#include "th10/game/background.hpp"
struct TextLog_0044b8e0 {
    char text[0x2000]; char* cursor; unsigned char dirty;
    __declspec(noinline) char* AppendLine(char* format, ...);
};
extern "C" {
extern unsigned int g_globals_stage; extern BackGroundCameraSnapshot g_back_camera;
extern FuncCtrl* g_func_ctrl; extern float g_game_speed;
SchedulerTask* __stdcall SchedulerTask_Create(void* callback);
}
#pragma code_seg(".text$01init")
extern "C" __declspec(noinline) int __stdcall BackGround_Initialize(BackGround* state, const char* name, int state_id) {
    if (state_id==0) g_background=state; else g_background_prev=state;
    state->stage_flags=g_globals_stage;
    if (state->Load(name)!=0) {
        ((TextLog_0044b8e0*)0x474f70)->AppendLine((char*)0x46cc70);
        return -1;
    }
    state->camera=g_back_camera;
    state->camera.camera.position=CameraVector(0.0f,0.0f,-600.0f);
    state->camera.camera.direction=CameraVector(0.0f,300.0f,600.0f);
    state->camera.camera.up=CameraVector(0.0f,1.0f,0.0f);
    state->camera.camera.eye_offset=CameraVector(0.0f,0.0f,0.0f);
    state->frame_limit=9610000.0f;
    SchedulerTask* callback=SchedulerTask_Create((void*)0x403050);
    callback->context=state; callback->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl,callback,state_id+12); state->primary=callback;
    callback=SchedulerTask_Create((void*)0x403060);
    callback->reserved_flags &= ~1u; callback->context=state;
    FuncCtrl_RegisterSecondary(g_func_ctrl,callback,state_id+7); state->secondary=callback;
    callback=SchedulerTask_Create((void*)0x403070);
    callback->context=state; callback->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl,callback,state_id+10); state->after_draw=callback;
    state->initialization_frame=0;
    // Finish publishing the callback before accessing the embedded timer.
    _ReadWriteBarrier();
    unsigned int timer_flags=state->timer_0038.flags;
    if (!(timer_flags&1)) {
        timer_flags|=1;
        state->timer_0038.current=0;
        state->timer_0038.previous=(int)0xfff0bdc1;
        state->timer_0038.elapsed=0;
        state->timer_0038.speed=&g_game_speed; state->timer_0038.flags=timer_flags;
    }
    // The lazy defaults and the following reset are separate observed writes.
    _ReadWriteBarrier();
    state->timer_0038.current=0; state->timer_0038.elapsed=0; state->timer_0038.previous=-1;
    // Commit the reset before publishing the active-state flag.
    _ReadWriteBarrier();
    state->state_flags|=1; state->value_094=0; state->value_0e0=0;
    return 0;
}
#pragma code_seg()
