#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/render/animation_resource_removal.hpp"
extern "C" void* g_func_ctrl;
extern "C" void* g_bullet_manager;
extern "C" SprtCtrl* g_sprt_ctrl;
extern "C" void __cdecl crt_free(void*);
void __cdecl operator delete(void*);
struct BulletSlot {
 unsigned char prefix[0x360];
 void* secondary_resource;
 unsigned char suffix[0x7F0-0x364];
 __declspec(noinline) BulletSlot();    // 0x00405D00
 __declspec(noinline) ~BulletSlot();
};
struct BulletManager2 {
 unsigned int flags,reserved_004;
 SchedulerTask* update_task; SchedulerTask* draw_task;
 unsigned char reserved_010[0x60-0x10];
 BulletSlot items[0x7D1];
 void* archive;
 BulletManager2() { memset(this,0,sizeof(*this));g_bullet_manager=this; }
 __declspec(noinline) ~BulletManager2();
 // 0x00405E20: load the bullet scripts and register the tasks; nonzero on failure.
 __declspec(noinline) int Initialize();
};
typedef char ItemSize[sizeof(BulletSlot)==0x7F0?1:-1];
typedef char ManagerSize[sizeof(BulletManager2)==0x3E0B54?1:-1];
typedef char ItemsOffset[offsetof(BulletManager2,items)==0x60?1:-1];
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl*,SchedulerTask*);
