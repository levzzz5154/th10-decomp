#include <string.h>
#include "collision.hpp"

struct AnimationManager10 {
    unsigned char reserved_00[0x4C];
    int script_tick_counter;                   // +0x4C
};

extern "C" void* g_sprt_ctrl;
extern "C" float g_game_speed;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
#pragma code_seg(".text$f0043e710F")
void* AnimationResourceFile::LoadScript(Entity* object, int index) {
    void* script = this->scripts[index];
    if (script == 0 || this->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return 0;
    }
    Entity_Init(0, object);
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
        object->time_scale = &g_game_speed;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    uint32_t* flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++static_cast<AnimationManager10*>(g_sprt_ctrl)->script_tick_counter;
    return g_sprt_ctrl;
}
#pragma code_seg()
