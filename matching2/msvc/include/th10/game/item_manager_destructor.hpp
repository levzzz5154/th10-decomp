#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/item_record.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* g_func_ctrl;
extern "C" void* g_item_manager;
extern "C" void __cdecl crt_free(void*);
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
struct ItemManager {
 unsigned int flags,reserved_004;
 SchedulerTask* primary; SchedulerTask* secondary;
 unsigned int field_010;
 Item elements[0x896];
 unsigned char tail[12];
 ItemManager() { memset(this,0,sizeof(*this));flags|=2;g_item_manager=this; }
 __declspec(noinline) ~ItemManager();
 // 0x0041AD90: register the update and draw tasks; nonzero on failure.
 __declspec(noinline) int Initialize();
 // 0x0041BA00: the update task; skipped while the game is paused or busy.
 int OnUpdate();
};
typedef char ManagerSize[sizeof(ItemManager)==0x21CEC0?1:-1];
typedef char ElementOffset[offsetof(ItemManager,elements)==0x14?1:-1];

__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl*,SchedulerTask*);
