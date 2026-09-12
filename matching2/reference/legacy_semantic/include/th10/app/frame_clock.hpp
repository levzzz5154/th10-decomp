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
    double minimum_sample;    // dbl_492540
    double wrap_bias;         // dbl_470B30 = 4294967296.0
    double millisecond_scale; // dbl_470B28 = 0.001
    // dbl_470B88 = 1000.0. dbl_492540 is shared with the QPC path, and after
    // the loc_438C82 seed it holds SECONDS on both paths. The millisecond arm
    // therefore has to scale it back up by 1000 before subtracting it from a
    // millisecond reading (0x00439540, loc_439622: fmul ds:dbl_470B88) - which
    // is exactly why the multiply produces the correct elapsed time.
    double minimum_scale;
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
    // 0x0044C150 against the thread record at 0x00492254. Not a log marker:
    // it raises the record's stop word, waits on the thread handle in 200 ms
    // slices, then CloseHandle()s it - the game thread join retail performs
    // before it reports "quit" or "restart" out of 0x00439390.
    void (*stop_game_thread)(void* context);
    // Device vtable +0xA4 is IDirect3DDevice9::BeginScene and +0xA8 is
    // EndScene, so the first of the two brackets the frame open. The two
    // slots used to be named the other way round.
    void (*begin_scene)(void* context);
    void (*reset_sprite_batch)(void* context);
    // dword_492378 is retail's CACHED D3DRS_FOGENABLE value - every fog site
    // reads it as `if (dword_492378 != 1) { flush; = 1; SetRenderState(28, 1) }`
    // (sub_402850) or the clear-to-0 form (sub_402CA0). Storing 0xFF is a cache
    // invalidation, not a fade level; the old name said the opposite.
    void (*invalidate_fog_cache)(void* context);
    void (*disable_fog)(void* context);
    void (*run_render_pass)(void* context);
    void (*clear_texture_stage)(void* context);
    void (*end_scene)(void* context);
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
