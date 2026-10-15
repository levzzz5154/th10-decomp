// 0x004231D0: open the death screen (continue or give up), or with result
// set the completed-game view.
#include "th10/game/pause_result_open_004231d0/open_state.hpp"
__forceinline void PauseOpenState::Open(bool result) {
    if (data_00477810->replay_mode == 1) {
        data_00491fb8 = (data_00491ff4 & 0x1000) ? 2 : 4;
        return;
    }
    phase = 6;
    timer.Set(0);
    data_00477810->flags |= 0x10;
    AnimationResource_00449870* resource = g_ascii_manager->cursor_resource;
    AnimationPool* pool = reinterpret_cast<AnimationPool*>(data_00491c10);
    Entity* object = pool->Allocate();
    reinterpret_cast<AnimationOpenFlags*>(&object->flags_35C)->render_enabled = 1;
    object->render_bucket = 15;
    resource->InitializeObject(object, 0);
    AnimationListsOpen* lists = reinterpret_cast<AnimationListsOpen*>(data_00491c10);
    {
        AnimationScriptId assigned = lists->RegisterSecondaryBack(object);
        cursor_animation = assigned;
    }
    AnimationHandle_00424480 cursor_handle;
    cursor_handle.value = (unsigned int)cursor_animation.value;
    reinterpret_cast<SpriteRegion_00424480*>(lists)->BindToAnimation(cursor_handle, 32, 16, 384, 448);
    resource = data_0047770c->result_resource;
    current_resource = resource;
    object = reinterpret_cast<AnimationPool*>(lists)->Allocate();
    reinterpret_cast<AnimationOpenFlags*>(&object->flags_35C)->render_enabled = 1;
    object->render_bucket = 15;
    resource->InitializeObject(object, result ? 129 : 128);
    {
        AnimationScriptId assigned = reinterpret_cast<AnimationListsOpen*>(data_00491c10)->RegisterSecondaryBack(object);
        background = assigned;
    }
    Music_Load(0, data_0046e0d8);
    if (data_00491d78 & 0x10)
        g_music_requests.RegisterResource(data_0046df98, 4, 0);
    g_music_requests.RegisterResource(data_0046df98, 2, 0);
    data_0047783c->result_track_heard = 1;
    result_flag = result ? 1 : 0;
    saved_speed = data_00476f78;
    data_00476f78 = 1.0f;
}
#pragma code_seg(".text$f004231d0F")
void PauseOpenState::OpenPause() { Open(false); }
#pragma code_seg()
