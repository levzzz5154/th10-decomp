#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* data_00491be4;
extern "C" void* data_00477840;
extern "C" void __cdecl entry_free_00452422(void*);
void __cdecl operator delete(void*);
struct EffectAnimation_00401FF0 : Entity {
 ~EffectAnimation_00401FF0();
};
struct EffectManager_0042B570 {
 unsigned int flags,reserved_004;
 SchedulerTask* update_task; SchedulerTask* draw_task;
 unsigned char reserved_010[8];
 EffectAnimation_00401FF0 animation;
 __declspec(noinline) ~EffectManager_0042B570();
};
typedef char AnimationSize[sizeof(EffectAnimation_00401FF0)==0x3AC?1:-1];
typedef char AnimationOffset[offsetof(EffectManager_0042B570,animation)==0x18?1:-1];
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler*,SchedulerTask*);
