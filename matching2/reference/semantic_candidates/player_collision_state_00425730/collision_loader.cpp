#include <string.h>
#include "collision.hpp"

struct AnimationManager_0043e710 {
    unsigned char reserved_00[0x4C];
    int script_tick_counter;                   // +0x4C
};

extern "C" void* data_00491c10;
extern "C" float data_00476f78;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
#pragma code_seg(".text$c40loader")
void AnimationResource_0043e710::LoadScript(Entity* object, int index) {
    void* script = this->scripts[index];
    if (script == 0 || this->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return;
    }
    Entity_Init(object);
    uint32_t mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptIndex() = static_cast<int16_t>(index);
    object->ScriptResourceId() = this->id;
    object->ScriptResource() = this;
    object->AnimationFlags() = mask;
    void* fresh = this->scripts[index];
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
    uint32_t* flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++static_cast<AnimationManager_0043e710*>(data_00491c10)->script_tick_counter;
}
#pragma code_seg()
