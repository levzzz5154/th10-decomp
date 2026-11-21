// Complete existing leaf bodies for a native caller-visibility control.
// Lookup and timer bodies copied from the maintained executor contexts.
#include "title_dispatcher.cpp"
#include "../../../../src/game/title/title_animation_slot_frames.cpp"
#include "../../../../src/core/sound/sound_queue.cpp"
#include "../../../../src/core/sprtlib/animation_manager_mark_resource_for_removal.cpp"
extern "C" float g_game_speed;
#pragma code_seg(".text$004491c0_fn")
void* __fastcall AnmLookup::Find(AnmLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnmLookupNode* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (AnmLookupNode* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
#include "../recovery_script_executor_caller_433ef0.cpp"
#pragma code_seg(".text$00409e50_title_fn")
void StopHandle2(StageReloadAnmHandle* handle) {
    AnimationScriptId id = { static_cast<int>(handle->id) };
    TitleAnmVm* object = static_cast<TitleAnmVm*>(
        reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = 1;
        if (object->children_flagged == 0) {
            for (TitleAnmChild* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()
