// Selected equivalent C++ body; see the script-change equivalence note.
#include "th10/render/animation_script_change.hpp"
#pragma code_seg(".text$01change")
void __stdcall ChangeAnimationScript(ScriptChangeResource* resource, Entity* object, int index) {
    void* script = resource->scripts[index];
    // The slot expression is written twice on purpose: load-merged to the one
    // register read, it reproduces the retail register allocation (see the
    // script-change equivalence note).
    if (!script || !resource->scripts[index] || resource->loading) return;
    object->ScriptIndex() = (short)index;
    unsigned int flags = object->AnimationFlags();
    object->ScriptResource() = resource;
    if (flags & 0x200) {
        float scale = object->scale_x * -1.0f;
        object->AnimationFlags() = (flags | 8) ^ 0x200u;
        object->scale_x = scale;
    }
    object->end_marker = 7;
    object->primary_color = 0xFFFFFFFFu;
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = (int)0xFFF0BDC1u;
    // MATCH: binding the two cleared header slots through local int& aliases
    // prevents MSVC from hoisting 0xFFF0BDC1 into EDI before primary_color.
    int& first_slot = *reinterpret_cast<int*>(&object->pad_0B4[0]);
    first_slot = 0;
    int& second_slot = *reinterpret_cast<int*>(&object->pad_100[0]);
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
    // MATCH: binding base+cursor through a local ScriptPair& alias preserves
    // the retail store ordering between AnimationFlags() and flags_06C.
    struct ScriptPair { void* base; void* cursor; };
    ScriptPair& pair = *reinterpret_cast<ScriptPair*>(&object->ScriptBase());
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
