#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* g_func_ctrl;
extern "C" void* g_smoll_score;
extern "C" void __cdecl crt_free(void*);
void __cdecl operator delete(void*);
struct EffectAnimation_00401FF0 : Entity {
 ~EffectAnimation_00401FF0();
};
struct SmollScoreDestructorView {
 unsigned int flags,reserved_004;
 SchedulerTask* update_task; SchedulerTask* draw_task;
 unsigned char reserved_010[8];
 EffectAnimation_00401FF0 animation;
 __declspec(noinline) ~SmollScoreDestructorView();
};
typedef char AnimationSize[sizeof(EffectAnimation_00401FF0)==0x3AC?1:-1];
typedef char AnimationOffset[offsetof(SmollScoreDestructorView,animation)==0x18?1:-1];
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove_00449F60(FuncCtrl*,SchedulerTask*);
