#define data_00491c10 stage_front_data_00491c10
#define data_0047770c stage_front_data_0047770c
#define data_00474c40 stage_front_data_00474c40
#define data_004776e0 stage_front_data_004776e0
#define data_00477704 stage_front_data_00477704
#define g_player stage_front_data_00477834
#define data_00477838 stage_front_data_00477838
#define data_0047783c stage_front_data_0047783c
#define data_00476f78 stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define data_00492590 stage_front_data_00492590
#include <string.h>
#include "front_view.hpp"

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
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
