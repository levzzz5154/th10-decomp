// =============================================================================
// frame_clock.cpp - Frame clock, frame advance, and device default state
// =============================================================================
#include "th10/app/frame_clock.hpp"

// Semantic reconstruction 0x00439540 - sample the frame clock under its lock.
// Uses timeGetTime (millisecond path) when no QPC frequency was captured,
// otherwise QueryPerformanceCounter deltas; both paths clamp against the
// lowest observed sample so the clock never runs backwards.
double Time_ReadSeconds(FrameClockState* state, const FrameClockHooks* hooks) {
    hooks->lock(hooks->context);
    double result;
    if (state->qpc_frequency == 0.0) {
        double now = hooks->read_millisecond_clock(hooks->context);
        if (now < 0.0)
            now += state->wrap_bias; // retail adds _DAT_00470B30 on wrap
        if (now < state->minimum_sample)
            state->minimum_sample = now;
        result = (now - state->minimum_sample) * state->millisecond_scale;
    } else {
        double counter = hooks->read_performance_counter(hooks->context);
        double delta = (counter - state->qpc_base) / state->qpc_frequency;
        if (delta < state->minimum_sample)
            state->minimum_sample = delta;
        result = delta - state->minimum_sample;
    }
    hooks->unlock(hooks->context);
    return result;
}

// Semantic reconstruction 0x00439390 - run one frame when the clock crosses
// deadline. Returns 0 (frame ran or slept), 1 (scheduler asked to quit), or
// 2 (scheduler asked for a full restart).
int Frame_Advance(FrameAdvanceState* state, const FrameAdvanceHooks* hooks) {
    double now = Time_ReadSeconds(state->clock, hooks->clock_hooks);
    state->sample = now;
    if (now < state->last_sample)
        state->deadline = now; // clock rewound: resynchronise
    state->last_sample = now;
    if (now <= state->deadline) {
        hooks->sleep_zero(hooks->context);
        return 0;
    }
    while (state->deadline < now)
        state->deadline += state->frame_interval;

    hooks->flush_sprite_batch(hooks->context);   // 0x00442F50
    hooks->select_primary_camera(hooks->context); // DAT_00491FAC binding
    hooks->apply_camera(hooks->context);         // 0x00421480
    hooks->set_viewport(hooks->context);         // device vtable +0xBC
    state->render_active = 1;

    int verdict = hooks->run_scheduler_frame(hooks->context); // 0x00449C00
    hooks->drain_sound_commands(hooks->context);              // 0x0043DDF0
    if (verdict == 0) {
        hooks->log_frame_marker(hooks->context); // 0x0044C150
        return 1;
    }
    if (verdict == -1) {
        hooks->log_frame_marker(hooks->context);
        return 2;
    }

    // Frame-skip accounting: present only every (skip_limit + 1) frames.
    state->skip_counter += 1;
    if (state->skip_counter >= state->skip_limit + 1) {
        hooks->end_scene(hooks->context);          // vtable +0xA4
        hooks->reset_sprite_batch(hooks->context); // manager +0x3ADAC8/..
        hooks->fade_reset(hooks->context);         // DAT_00492378 = 0xFF
        hooks->disable_fog(hooks->context);        // 0x00420CD0
        hooks->run_render_pass(hooks->context);    // 0x00449D40
        hooks->flush_sprite_batch(hooks->context); // 0x00442F50
        hooks->clear_texture_stage(hooks->context); // SetTexture(0, 0)
        hooks->begin_scene(hooks->context);        // vtable +0xA8
        state->skip_counter = 0;
        hooks->present(hooks->context);            // 0x004391F0
    }
    state->frame_cost = Time_ReadSeconds(state->clock, hooks->clock_hooks) - now;
    return 0;
}

// Semantic reconstruction 0x00439D20 - reapply fixed-function device state,
// texture-stage, and sampler state the game relies on after reset/boot.
void Device_ApplyDefaultState(const DeviceStateHooks* hooks,
                              unsigned char* manager_flags) {
    static const unsigned int kRenderStates[][2] = {
        {0x07, 1},          // D3DRS_ZENABLE-adjacent block in retail order
        {0x89, 0},          {0x16, 1},          {0x1B, 1},
        {0x09, 2},          {0x13, 5},          {0x14, 6},
        {0x17, 8},          {0x0F, 1},          {0x18, 1},
        {0x19, 7},          {0x1C, 1},          {0x26, 0x3F800000u},
        {0x23, 0},          {0x8C, 3},          {0x22, 0xFFA0A0A0u},
        {0x24, 0x447A0000u},{0x25, 0x459C4000u},{0xA1, 0},
    };
    static const unsigned int kStageStates[][3] = {
        {0, 0x04, 4}, {0, 0x05, 2}, {0, 0x06, 3}, {0, 0x01, 4},
        {0, 0x02, 2}, {0, 0x03, 3}, {0, 0x18, 2}, {0, 0x0B, 0},
    };
    static const unsigned int kSamplerStates[][3] = {
        {0, 7, 0}, {0, 5, 2}, {0, 6, 2}, {0, 3, 3}, {0, 1, 1}, {0, 2, 1},
    };
    for (const auto& entry : kRenderStates)
        hooks->set_render_state(hooks->context, entry[0], entry[1]);
    for (const auto& entry : kStageStates)
        hooks->set_texture_stage_state(hooks->context, entry[0], entry[1],
                                       entry[2]);
    for (const auto& entry : kSamplerStates)
        hooks->set_sampler_state(hooks->context, entry[0], entry[1],
                                 entry[2]);
    if (manager_flags != 0) {
        // g_pGameStateManager + 0x3ADA64..6C: blend mode 3, colours 0xFF,
        // batch pointer cleared.
        manager_flags[4] = 3;      // +0x3ADA68
        manager_flags[5] = 0xFF;   // +0x3ADA69
        manager_flags[6] = 0xFF;   // +0x3ADA6A
        manager_flags[0] = 0;      // +0x3ADA64 (dword low byte)
        manager_flags[1] = 0;
        manager_flags[2] = 0;
        manager_flags[3] = 0;
        manager_flags[8] = 0xFF;   // +0x3ADA6C
    }
}
