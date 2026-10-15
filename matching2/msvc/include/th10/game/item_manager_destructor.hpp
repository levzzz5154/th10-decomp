#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* g_func_ctrl;
extern "C" void* data_00477818;
extern "C" void __cdecl entry_free_00452422(void*);
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
struct Item: Entity {
 unsigned char extension[0x44];
 __declspec(noinline) Item();
 __declspec(noinline) ~Item();
 uint32_t& Flags_3D8() { return *(uint32_t*)((unsigned char*)this+0x3D8); }
};
struct ItemManager {
 unsigned int flags,reserved_004;
 SchedulerTask* primary; SchedulerTask* secondary;
 unsigned int field_010;
 Item elements[0x896];
 unsigned char tail[12];
 ItemManager() { memset(this,0,sizeof(*this));flags|=2;data_00477818=this; }
 __declspec(noinline) ~ItemManager();
 // 0x0041AD90: register the update and draw tasks; nonzero on failure.
 __declspec(noinline) int Initialize();
 // 0x0041BA00: the update task; skipped while the game is paused or busy.
 int OnUpdate();
};
typedef char ElementSize[sizeof(Item)==0x3F0?1:-1];
typedef char ManagerSize[sizeof(ItemManager)==0x21CEC0?1:-1];
typedef char ElementOffset[offsetof(ItemManager,elements)==0x14?1:-1];

__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove_00449F60(FuncCtrl*,SchedulerTask*);
