// Complete non-preserving loader at 0x0043E710. Unlike 0x43E7E0, this body
// initializes the object before assigning and running the selected script.
#include <string.h>
#include "types.hpp"
struct MovementAnimationCounter {
    unsigned char reserved[0x4C];
    int script_tick_counter;
};
#pragma code_seg(".text$0043e710_fn")
void* __stdcall MovementLoadScript(int index, AnimationResource_00449870* resource, Entity* object) {
    void* script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return 0;
    }
    Entity_Init(script, object);
    unsigned int flags = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptIndex() = static_cast<short>(index);
    object->ScriptResourceId() = resource->id;
    object->ScriptResource() = resource;
    object->AnimationFlags() = flags;
    void* fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = static_cast<int>(0xFFF0BDC1u);
        object->frame_elapsed = 0.0f;
        object->time_scale = &data_00476f78;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    object->AnimationFlags() &= ~1u;
    RunAnimationVm_0043ee30(object);
    MovementAnimationCounter* manager = reinterpret_cast<MovementAnimationCounter*>(data_00491c10);
    ++manager->script_tick_counter;
    return manager;
}
#pragma code_seg()
