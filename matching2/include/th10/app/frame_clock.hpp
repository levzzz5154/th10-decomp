// =============================================================================
// frame_clock.hpp - Frame clock and frame-advance surfaces
// Retail functions: 0x00439540, 0x00439390, 0x00439D20
// =============================================================================
#ifndef TH10_APP_FRAME_CLOCK_HPP
#define TH10_APP_FRAME_CLOCK_HPP

struct FrameClockHooks {
    void* context;
    void (*lock)(void* context);      // EnterCS(&DAT_004922EC) + counter
    void (*unlock)(void* context);
    double (*read_millisecond_clock)(void* context);   // timeGetTime path
    double (*read_performance_counter)(void* context); // QPC path
};

struct FrameClockState {
    double qpc_frequency;     // DAT_00492508/0C (0 => millisecond path)
    double qpc_base;          // DAT_00492510/14
    double minimum_sample;    // _DAT_00492540
    double wrap_bias;         // _DAT_00470B30
    double millisecond_scale; // _DAT_00470B28
};

double Time_ReadSeconds(FrameClockState* state, const FrameClockHooks* hooks);

struct FrameAdvanceState {
    FrameClockState* clock;
    double sample;         // ctx+0x38
    double last_sample;    // ctx+0x40
    double deadline;       // ctx+0x48
    double frame_interval; // _DAT_00470C90
    double frame_cost;     // _DAT_004923A0
    int render_active;     // _DAT_00491FB0
    int skip_counter;      // byte ctx+0x14
    int skip_limit;        // DAT_00491D66
};

struct FrameAdvanceHooks {
    void* context;
    const FrameClockHooks* clock_hooks;
    void (*sleep_zero)(void* context);
    void (*flush_sprite_batch)(void* context);
    void (*select_primary_camera)(void* context);
    void (*apply_camera)(void* context);
    void (*set_viewport)(void* context);
    int (*run_scheduler_frame)(void* context);
    void (*drain_sound_commands)(void* context);
    void (*log_frame_marker)(void* context);
    void (*end_scene)(void* context);
    void (*reset_sprite_batch)(void* context);
    void (*fade_reset)(void* context);
    void (*disable_fog)(void* context);
    void (*run_render_pass)(void* context);
    void (*clear_texture_stage)(void* context);
    void (*begin_scene)(void* context);
    void (*present)(void* context);
};

int Frame_Advance(FrameAdvanceState* state, const FrameAdvanceHooks* hooks);

struct DeviceStateHooks {
    void* context;
    void (*set_render_state)(void* context, unsigned int state,
                             unsigned int value);
    void (*set_texture_stage_state)(void* context, unsigned int stage,
                                    unsigned int state, unsigned int value);
    void (*set_sampler_state)(void* context, unsigned int sampler,
                              unsigned int state, unsigned int value);
};

void Device_ApplyDefaultState(const DeviceStateHooks* hooks,
                              unsigned char* manager_flags);

#endif // TH10_APP_FRAME_CLOCK_HPP
