#include "../sprtlib/animation_handle_change_script.cpp"
// Selected equivalent C++ body; see the script-change equivalence note.
#include "th10/render/animation_script_change.hpp"
#pragma code_seg(".text$01change")
void __stdcall ChangeAnimationScript(ScriptChangeResource* resource, Entity* object, int index) {
    void* script = resource->scripts[index];
    if (!script || resource->loading) return;
    object->ScriptIndex() = (short)index;
    unsigned int flags = object->AnimationFlags();
    object->ScriptResource() = resource;
    if (flags & 0x200) {
        float scale = object->scale_x * -1.0f;
        flags = (flags | 8) ^ 0x200;
        object->AnimationFlags() = flags;
        object->scale_x = scale;
    }
    object->end_marker = 7;
    object->primary_color = 0xFFFFFFFFu;
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = (int)0xFFF0BDC1u;
    int& first_slot = *(int*)((char*)object+0xB4);
    first_slot = 0;
    int& second_slot = *(int*)((char*)object+0x100);
    second_slot = 0;
    object->pad_12C[0] = 0;
    object->pad_178[0] = 0;
    object->pad_1B4[0] = 0;
    object->pad_200[0] = 0;
    object->pad_22C[0] = 0;
    object->ScriptResourceId() = resource->id;
    unsigned int mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    struct ScriptPair { void* base; void* cursor; };
    ScriptPair& pair = *(ScriptPair*)((char*)object + 0x38C);
    pair.base = script;
    pair.cursor = script;
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
    RunChangeScriptVm(object);
    ++g_sprt_ctrl->script_tick_counter;
}
#pragma code_seg()

#include "../../../build_support/layout/ltcg/script_change_find_anchor.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall ScriptChangeCompilerContext(ScriptChangeHandle* handles, int count, int index) {
    while (count--) { handles->ChangeScript(index); ++handles; }
    return index;
}
#pragma code_seg()
