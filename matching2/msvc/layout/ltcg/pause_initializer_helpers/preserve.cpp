#include <string.h>
#include "th10/game/pause_initializer_00422ab0.hpp"
struct AnimationObject_0043e7e0 : Entity {};
struct AnimationResource_0043e7e0 { unsigned short id; unsigned char reserved_002[0x11A]; void** scripts; unsigned char reserved_120[4]; int loading; };
struct AnimationManager_0043e7e0 { unsigned char reserved[0x4C]; int script_tick_counter; };
extern "C" AnimationLookupContext* data_00491c10;
extern "C" float data_00476f78;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
#pragma code_seg(".text$10preserve")
__declspec(noinline) void __stdcall LoadScriptPreservingState_0043e7e0(
    AnimationResource_0043e7e0* resource, AnimationObject_0043e7e0* object, int index) {
    void* script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return;
    }
    object->ScriptIndex() = (short)index;
    object->ScriptResourceId() = resource->id;
    unsigned int mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void* fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = (int)0xFFF0BDC1u;
        object->frame_elapsed = 0.0f;
        object->time_scale = &data_00476f78;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    unsigned int* flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++((AnimationManager_0043e7e0*)data_00491c10)->script_tick_counter;
}
#pragma code_seg()
