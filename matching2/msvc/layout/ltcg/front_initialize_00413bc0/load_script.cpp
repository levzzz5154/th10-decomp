#include <string.h>
#include "th10/game/front_initialize_00413bc0.hpp"

struct AnimationManager_0043e710 {
    unsigned char reserved_00[0x4C];
    int script_tick_counter; // +0x4C
};

extern "C" float data_00476f78;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity *object);
extern "C" void __stdcall LoadScript_0043e710(AnimationResource_0043e710 *resource,
                                              AnimationObject_0043e710 *object, int index);

#pragma code_seg(".text$0043e710_fn")
__declspec(noinline) void __stdcall LoadScript_0043e710(AnimationResource_0043e710 *resource,
                                                        AnimationObject_0043e710 *object,
                                                        int index) {
    void *script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return;
    }
    Entity_Init(script, object); // leading slot is dead in this ABI
    uint32_t mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptIndex() = static_cast<int16_t>(index);
    object->ScriptResourceId() = resource->id;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void *fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = static_cast<int32_t>(0xFFF0BDC1u);
        object->frame_elapsed = 0.0f;
        object->time_scale = &data_00476f78;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    uint32_t *flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++reinterpret_cast<AnimationManager_0043e710 *>(data_00491c10)->script_tick_counter;
}
#pragma code_seg()
