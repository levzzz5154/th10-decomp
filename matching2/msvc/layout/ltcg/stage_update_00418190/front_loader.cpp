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
#include "th10/game/entity.hpp"
struct AnimationObject_0043e7e0 : Entity {};
struct AnimationResource_0043e7e0 {
    unsigned short id;
    unsigned char reserved_002[0x11A];
    void **scripts;
    unsigned char reserved_120[4];
    int loading;
};
struct AnimationManager_0043e7e0 {
    unsigned char reserved[0x4C];
    int script_tick_counter;
};
struct FrontAnimationLookup;
extern "C" FrontAnimationLookup *data_00491c10;
extern "C" float data_00476f78;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity *object);
#pragma code_seg(".text$0043e7e0_fn")
__declspec(noinline) void *__stdcall
InitializePreservingLoader_0043e7e0(AnimationResource_0043e7e0 *resource,
                                    AnimationObject_0043e7e0 *object, int index) {
    void *script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return 0;
    }
    object->ScriptIndex() = (short)index;
    object->ScriptResourceId() = resource->id;
    unsigned int mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void *fresh = resource->scripts[index];
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
    unsigned int *flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    AnimationManager_0043e7e0 *manager = (AnimationManager_0043e7e0 *)data_00491c10;
    ++manager->script_tick_counter;
    return manager;
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
