#include <string.h>
#include "th10/game/entity.hpp"
struct AnimationObject4 : Entity {};
struct AnimationResource4 { unsigned short id; unsigned char reserved_002[0x11A]; void** scripts; unsigned char reserved_120[4]; int loading; };
struct AnimationManager11 { unsigned char reserved[0x4C]; int script_tick_counter; };
extern "C" void* g_sprt_ctrl;
extern "C" float g_game_speed;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
#pragma code_seg(".text$f0043e7e0F")
__declspec(noinline) void __stdcall LoadScriptPreservingState(
    AnimationResource4* resource, AnimationObject4* object, int index) {
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
        object->time_scale = &g_game_speed;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    unsigned int* flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++((AnimationManager11*)g_sprt_ctrl)->script_tick_counter;
}
#pragma code_seg()
