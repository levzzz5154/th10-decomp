// Complete 0x00422AB0 pause-state initializer with its actual one-stack-input boundary.
#include "th10/game/pause_initializer_00422ab0.hpp"
#pragma code_seg(".text$06pause")
extern "C" __declspec(noinline) void __stdcall PauseMenu_Initialize_00422ab0(PauseUpdateView* state) {
    unsigned int& phase = state->phase;
    phase = 1;
    if (!(state->timer_flags & 1)) {
        state->current_frame = 0;
        state->previous_frame = 0xFFF0BDC1;
        state->elapsed = 0.0f;
        state->speed = &g_game_speed;
        state->timer_flags |= 1;
    }
    state->current_frame = 0;
    state->elapsed = 0.0f;
    state->previous_frame = -1;
    g_game->flags |= 0x10;
    AnimationBank* first_resource = g_ascii_manager->resource;
    Entity* first = reinterpret_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int first_flags = first->AnimationFlags();
    first->render_bucket = 15;
    first->AnimationFlags() = first_flags | 0x40000000;
    first_resource->InitializeObject(first, 0);
    Handle4 handle;
    AnimationLookupContext* manager = g_sprt_ctrl;
    reinterpret_cast<AnimationSecondaryLists*>(manager)->RegisterSecondaryBack(&handle, first);
    state->cursor_animation = handle;
    AnimationHandle_00424480 descriptor_handle;
    descriptor_handle.value = handle.value;
    reinterpret_cast<SpriteRegion_00424480*>(manager)->BindToAnimation(descriptor_handle, 32, 16, 384, 448);
    AnimationBank* second_resource = g_front->resource;
    state->resource = second_resource;
    Entity* second = reinterpret_cast<AnimationPool*>(manager)->Allocate();
    unsigned int second_flags = second->AnimationFlags();
    second->render_bucket = 15;
    second->AnimationFlags() = second_flags | 0x40000000;
    second_resource->InitializeObject(second, 121);
    reinterpret_cast<AnimationSecondaryLists*>(g_sprt_ctrl)->RegisterSecondaryBack(&handle, second);
    state->background = handle;
    state->background.StopAtFrame3();
    g_sound_manager.Queue(32, 0);
    reinterpret_cast<AnimationManager_0043e460*>(&g_sound_manager)->RegisterResource(str_pause, 6, 0);
    if (g_game->replay_mode) {
        state->background.FindChildRef(117).MarkAndClear();
    }
    state->saved_speed = g_game_speed;
    g_game_speed = 1.0f;
}
#pragma code_seg()
