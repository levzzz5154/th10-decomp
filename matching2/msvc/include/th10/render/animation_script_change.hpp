#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
struct ScriptChangeResource {
    unsigned short id;
    unsigned char reserved_002[0x11A];
    void** scripts;
    unsigned char reserved_120[4];
    int loading;
};
struct ScriptChangeLink { Entity* object; ScriptChangeLink* next; ScriptChangeLink* previous; };
struct ScriptChangeContext {
    unsigned char reserved_000[0x4C];
    int script_tick_counter;
    unsigned char reserved_050[0x72DAD4-0x50];
    ScriptChangeLink* primary;
    int reserved_72dad8;
    ScriptChangeLink* secondary;
};
struct ScriptChangeId { int value; };
struct ScriptChangeManager {
    __declspec(noinline) Entity* __fastcall Find(ScriptChangeContext* context, ScriptChangeId id);
};
struct ScriptChangeHandle {
    ScriptChangeId id;
    __declspec(noinline) void ChangeScript(int index);
};
extern "C" ScriptChangeContext* g_sprt_ctrl;
extern "C" float g_game_speed;
extern "C" float flt_neg1;
extern "C" void __stdcall RunChangeScriptVm(Entity* object);
extern "C" __declspec(noinline) void __stdcall ChangeAnimationScript(ScriptChangeResource* resource, Entity* object, int index);

// Field extents used by the real lookup and script changer.
typedef char ScriptChangeIdSize[sizeof(ScriptChangeId) == 4 ? 1 : -1];
typedef char ScriptChangeHandleSize[sizeof(ScriptChangeHandle) == 4 ? 1 : -1];
typedef char ScriptChangeTableOffset[offsetof(ScriptChangeResource, scripts) == 0x11C ? 1 : -1];
typedef char ScriptChangeLoadingOffset[offsetof(ScriptChangeResource, loading) == 0x124 ? 1 : -1];
typedef char ScriptChangeCounterOffset[offsetof(ScriptChangeContext, script_tick_counter) == 0x4C ? 1 : -1];
typedef char ScriptChangePrimaryOffset[offsetof(ScriptChangeContext, primary) == 0x72DAD4 ? 1 : -1];
typedef char ScriptChangeSecondaryOffset[offsetof(ScriptChangeContext, secondary) == 0x72DADC ? 1 : -1];
