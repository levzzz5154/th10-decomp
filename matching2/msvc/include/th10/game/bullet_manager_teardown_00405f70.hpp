#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/render/animation_resource_removal.hpp"
extern "C" void* data_00491be4;
extern "C" void* data_004776f0;
extern "C" AnimationManager* data_00491c10;
extern "C" void __cdecl entry_free_00452422(void*);
void __cdecl operator delete(void*);
struct BulletSlot_00405DE0 {
 unsigned char prefix[0x360];
 void* secondary_resource;
 unsigned char suffix[0x7F0-0x364];
 __declspec(noinline) ~BulletSlot_00405DE0();
};
struct BulletManager_00405F70 {
 unsigned int flags,reserved_004;
 SchedulerTask* update_task; SchedulerTask* draw_task;
 unsigned char reserved_010[0x60-0x10];
 BulletSlot_00405DE0 items[0x7D1];
 void* archive;
 __declspec(noinline) ~BulletManager_00405F70();
};
typedef char ItemSize[sizeof(BulletSlot_00405DE0)==0x7F0?1:-1];
typedef char ManagerSize[sizeof(BulletManager_00405F70)==0x3E0B54?1:-1];
typedef char ItemsOffset[offsetof(BulletManager_00405F70,items)==0x60?1:-1];
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler*,SchedulerTask*);
