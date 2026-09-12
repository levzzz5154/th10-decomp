#pragma once

#include <cstdint>

struct GameplayRenderRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct GameplayRenderState {
    uint32_t flags;
    int transition_timer;
    int transition_frame;
    uint8_t tint_active;
    uint32_t tint_color;
    int secondary_tint;
    int activity_counter;
    int render_resources;
    int transient[3];
    int layer_active[8];
    uint32_t render_seed_a;
    uint32_t render_seed_b;
    uint32_t render_state_22;
    uint32_t render_state_24;
    uint32_t render_state_25;
    uint8_t render_snapshot[0x118];
};

struct GameplayRenderGlobals {
    int tint_enabled;
    uint32_t tint_color;
    int mode_28_initialized;
    uint32_t seed_a;
    uint32_t seed_b;
};

struct GameplayRenderHooks {
    void* context;
    void (*flush_state)(void* context);
    void (*apply_snapshot)(void* context, const void* snapshot);
    void (*set_render_state)(void* context, int state, uint32_t value);
    void (*clear_target)(void* context, uint32_t color);
    void (*draw_rect)(void* context, const GameplayRenderRect* rect,
                      uint32_t color);
    void (*create_transition_text)(void* context);
    void (*start_transition)(void* context, int value);
    void (*stop_runtime)(void* context);
    void (*reset_audio)(void* context);
    void (*draw_resource)(void* context, int index);
    void (*draw_layer)(void* context, int index);
};

// 0x00402850 - Execute the gameplay render/transition pass.
int GameplayRenderPass_Run(GameplayRenderState* state,
                           GameplayRenderGlobals* globals,
                           const GameplayRenderHooks* hooks);
