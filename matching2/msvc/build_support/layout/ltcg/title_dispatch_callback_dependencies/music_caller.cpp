// Complete existing leaf bodies for a native caller-visibility control.
// Lookup and timer bodies copied from the maintained executor contexts.
#include "title_dispatcher.cpp"
#include "../../../../src/game/title/recovery_animation_slot_frames_0042c6d0.cpp"
#include "../../../../src/core/sound/animation_manager_queue_resource_0043dc90.cpp"
#include "../../../../src/core/sprtlib/animation_manager_mark_resource_for_removal_004493e0.cpp"
extern "C" float g_game_speed;
#pragma code_seg(".text$004491c0_fn")
void* __fastcall RecoveryLookup::Find(RecoveryLookupContext* context, RecoveryScriptId id) {
    if (!id.value)
        return 0;
    for (RecoveryLookupNode* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (RecoveryLookupNode* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
#include "../recovery_script_executor_caller_00433ef0.cpp"
#pragma code_seg(".text$00409e50_title_fn")
void StopHandle_00409e50(AnimationHandle_0040c3c0* handle) {
    RecoveryScriptId id = { static_cast<int>(handle->id) };
    RecoveryMusicVm* object = static_cast<RecoveryMusicVm*>(
        reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = 1;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()
