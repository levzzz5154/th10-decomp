#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* g_func_ctrl;
extern "C" void* g_smoll_score;
extern "C" void __cdecl crt_free(void*);
void __cdecl operator delete(void*);
struct EffectAnimation : Entity {
 ~EffectAnimation();
};
struct SmollScoreDestructorView {
 unsigned int flags,reserved_004;
 SchedulerTask* update_task; SchedulerTask* draw_task;
 unsigned char reserved_010[8];
 EffectAnimation animation;
 __declspec(noinline) ~SmollScoreDestructorView();
};
typedef char AnimationSize[sizeof(EffectAnimation)==0x3AC?1:-1];
typedef char AnimationOffset[offsetof(SmollScoreDestructorView,animation)==0x18?1:-1];
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl*,SchedulerTask*);
