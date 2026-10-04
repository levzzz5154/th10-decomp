#include "title_dispatcher.cpp"
#include "../../../msvc/layout/ltcg/recovery_animation_slot_frames_0042c6d0_context.cpp"
#pragma code_seg(".text$00409e50_title_fn")
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
struct TitleRuntime : RecoveryMusicRoom_00433ef0 {
    __declspec(noinline) int Update();
};
#pragma code_seg(".text$0042d2e0_fn")
int TitleRuntime::Update() {
    return TitleDispatcher_Update_0042cdf0(this);
}
#pragma code_seg()
