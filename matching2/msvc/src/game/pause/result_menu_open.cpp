// Open the pause result view or the completed-game result view.
#include "th10/game/pause_result_open/open_state.hpp"
__forceinline void PauseOpenState::Open(bool result) {
    if (g_game->replay_mode == 1) {
        g_main_state = (g_app_flags & 0x1000) ? 2 : 4;
        return;
    }
    phase = 6;
    timer.Set(0);
    g_game->flags |= 0x10;
    AnimationBank* resource = g_ascii_manager->cursor_resource;
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
    AnimationHandle8 cursor_handle;
    cursor_handle.value = (unsigned int)cursor_animation.value;
    reinterpret_cast<SpriteRegion*>(lists)->BindToAnimation(cursor_handle, 32, 16, 384, 448);
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
    Music_Load(0, str_bgm_th10_17_wav);
    if (g_sound_flags & 0x10)
        g_music_requests.RegisterResource(str_dummy, 4, 0);
    g_music_requests.RegisterResource(str_dummy, 2, 0);
    g_score->result_track_heard = 1;
    result_flag = result ? 1 : 0;
    saved_speed = g_game_speed;
    g_game_speed = 1.0f;
}
#pragma code_seg(".text$00423370_fn")
void PauseOpenState::OpenResult() { Open(true); }
#pragma code_seg()
#include "../../../build_support/layout/ltcg/result_open/allocate.cpp"
#include "../../../build_support/layout/ltcg/result_open/descriptor.cpp"
#include "../../../build_support/layout/ltcg/result_open/entity_init.cpp"
#include "../../../build_support/layout/ltcg/result_open/find.cpp"
#include "../../../build_support/layout/ltcg/result_open/music.cpp"
#include "../../../build_support/layout/ltcg/result_open/registrar.cpp"
#include "../../../build_support/layout/ltcg/result_open/secondary_back.cpp"
