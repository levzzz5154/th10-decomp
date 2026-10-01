#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
extern "C" void* data_00491be4;
extern "C" void* data_00477818;
extern "C" void __cdecl entry_free_00452422(void*);
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
struct NativeEffectElement_0041AD60: Entity {
 unsigned char extension[0x44];
 __declspec(noinline) NativeEffectElement_0041AD60();
 __declspec(noinline) ~NativeEffectElement_0041AD60();
 uint32_t& Flags_3D8() { return *(uint32_t*)((unsigned char*)this+0x3D8); }
};
struct NativeEffectManager_0041ADF0 {
 unsigned int flags,reserved_004;
 SchedulerTask* primary; SchedulerTask* secondary;
 unsigned int field_010;
 NativeEffectElement_0041AD60 elements[0x896];
 unsigned char tail[12];
 NativeEffectManager_0041ADF0() { memset(this,0,sizeof(*this));flags|=2;data_00477818=this; }
 __declspec(noinline) ~NativeEffectManager_0041ADF0();
};
typedef char ElementSize[sizeof(NativeEffectElement_0041AD60)==0x3F0?1:-1];
typedef char ManagerSize[sizeof(NativeEffectManager_0041ADF0)==0x21CEC0?1:-1];
typedef char ElementOffset[offsetof(NativeEffectManager_0041ADF0,elements)==0x14?1:-1];

__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler*,SchedulerTask*);
