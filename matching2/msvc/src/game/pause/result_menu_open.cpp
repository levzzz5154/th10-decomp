// Open the pause result view or the completed-game result view.
#include "th10/game/pause_result_open_004231d0/open_state.hpp"
__forceinline void PauseOpenState::Open(bool result) {
    if (g_game->replay_mode == 1) {
        data_00491fb8 = (data_00491ff4 & 0x1000) ? 2 : 4;
        return;
    }
    phase = 6;
    timer.Set(0);
    g_game->flags |= 0x10;
    AnimationResource_00449870* resource = g_ascii_manager->cursor_resource;
    AnimationPool* pool = reinterpret_cast<AnimationPool*>(g_sprt_ctrl);
    Entity* object = pool->Allocate();
    reinterpret_cast<AnimationOpenFlags*>(&object->flags_35C)->render_enabled = 1;
    object->render_bucket = 15;
    resource->InitializeObject(object, 0);
    AnimationListsOpen* lists = reinterpret_cast<AnimationListsOpen*>(g_sprt_ctrl);
    {
        AnimationScriptId assigned = lists->RegisterSecondaryBack(object);
        cursor_animation = assigned;
    }
    AnimationHandle_00424480 cursor_handle;
    cursor_handle.value = (unsigned int)cursor_animation.value;
    reinterpret_cast<SpriteRegion_00424480*>(lists)->BindToAnimation(cursor_handle, 32, 16, 384, 448);
    resource = g_front->result_resource;
    current_resource = resource;
    object = reinterpret_cast<AnimationPool*>(lists)->Allocate();
    reinterpret_cast<AnimationOpenFlags*>(&object->flags_35C)->render_enabled = 1;
    object->render_bucket = 15;
    resource->InitializeObject(object, result ? 129 : 128);
    {
        AnimationScriptId assigned = reinterpret_cast<AnimationListsOpen*>(g_sprt_ctrl)->RegisterSecondaryBack(object);
        background = assigned;
    }
    Music_Load(0, data_0046e0d8);
    if (data_00491d78 & 0x10)
        g_music_requests.RegisterResource(data_0046df98, 4, 0);
    g_music_requests.RegisterResource(data_0046df98, 2, 0);
    g_score->result_track_heard = 1;
    result_flag = result ? 1 : 0;
    saved_speed = g_game_speed;
    g_game_speed = 1.0f;
}
#pragma code_seg(".text$00423370_fn")
void PauseOpenState::OpenResult() { Open(true); }
#pragma code_seg()
#include "../../../build_support/layout/ltcg/result_open_00423370/allocate.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/descriptor.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/entity_init.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/find.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/music.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/registrar.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/secondary_back.cpp"
