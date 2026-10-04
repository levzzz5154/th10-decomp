// Complete existing leaf bodies for a native caller-visibility control.
// Lookup and timer bodies copied from the maintained executor contexts.
#include "title_dispatcher.cpp"
#include "../../../msvc/src/game/recovery_animation_slot_frames_0042c6d0.cpp"
#include "../../../msvc/src/game/recovery_install_animation_slot_0042c670.cpp"
#include "../../../msvc/src/render/animation_manager_queue_resource_0043dc90.cpp"
#include "../../../msvc/src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"
extern "C" float data_00476f78;
#pragma code_seg(".text$004491c0_fn")
void* __fastcall RecoveryLookup_0040bd80::Find(RecoveryLookupContext_0040bd80* context, RecoveryScriptId_0040bd80 id) {
    if (!id.value)
        return 0;
    for (RecoveryLookupNode_0040bd80* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (RecoveryLookupNode_0040bd80* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
static __forceinline void MusicResetTimer(RecoveryTimer_0040bd80* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &data_00476f78;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}

#pragma code_seg(".text$0042c5c0_fn")
void RecoveryMusicRoom_00433ef0::DisableTimerWithOwner(int owner) {
    int* request = &timer_owner;
    request[0] = owner;
    request[1] = 0;
    MusicResetTimer(&timer);
}
#pragma code_seg(".text$0042c620_fn")
void RecoveryMusicRoom_00433ef0::SetTimerTarget(int target) {
    phase = target;
    MusicResetTimer(&timer);
}

#pragma code_seg(".text$00409e50_fn")
void StopHandle_00409e50(AnimationHandle_0040c3c0* handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle->id) };
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
    if (object != 0) {
        object->stop_frame = 1;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()
