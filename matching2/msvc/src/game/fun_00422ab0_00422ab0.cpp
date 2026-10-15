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
        state->speed = &data_00476f78;
        state->timer_flags |= 1;
    }
    state->current_frame = 0;
    state->elapsed = 0.0f;
    state->previous_frame = -1;
    data_00477810->flags |= 0x10;
    AnimationResource_00449870* first_resource = g_ascii_manager->resource;
    Entity* first = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int first_flags = first->AnimationFlags();
    first->render_bucket = 15;
    first->AnimationFlags() = first_flags | 0x40000000;
    first_resource->InitializeObject(first, 0);
    Handle4 handle;
    AnimationLookupContext* manager = data_00491c10;
    reinterpret_cast<AnimationSecondaryLists*>(manager)->RegisterSecondaryBack(&handle, first);
    state->cursor_animation = handle;
    AnimationHandle_00424480 descriptor_handle;
    descriptor_handle.value = handle.value;
    reinterpret_cast<SpriteRegion_00424480*>(manager)->BindToAnimation(descriptor_handle, 32, 16, 384, 448);
    AnimationResource_00449870* second_resource = data_0047770c->resource;
    state->resource = second_resource;
    Entity* second = reinterpret_cast<AnimationPool*>(manager)->Allocate();
    unsigned int second_flags = second->AnimationFlags();
    second->render_bucket = 15;
    second->AnimationFlags() = second_flags | 0x40000000;
    second_resource->InitializeObject(second, 121);
    reinterpret_cast<AnimationSecondaryLists*>(data_00491c10)->RegisterSecondaryBack(&handle, second);
    state->background = handle;
    state->background.StopAtFrame3();
    data_00492590.Queue(32, 0);
    reinterpret_cast<AnimationManager_0043e460*>(&data_00492590)->RegisterResource(data_0046e0c0, 6, 0);
    if (data_00477810->replay_mode) {
        state->background.FindChildRef(117).MarkAndClear();
    }
    state->saved_speed = data_00476f78;
    data_00476f78 = 1.0f;
}
#pragma code_seg()
