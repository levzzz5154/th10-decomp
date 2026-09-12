#pragma once

#include <cstdint>

struct ScoreRuntimeUiState {
    uint32_t flags;
    int previous_frame;
    int frame;
    float frame_accumulator;
    const float* frame_scale;
    int displayed_score;
    int target_score;
    int score_decay_end_frame;
    int metric_index;
    int16_t stage_modes[8];
    int16_t effect_modes[5];
    float camera_position[3];
};

struct ScoreRuntimeUiEnv {
    uint32_t* release_flags;
    float playfield_x;
    int metric_a;
    int metric_b;
    const float* player_position;
};

struct ScoreRuntimeUiOps {
    void* context;
    void (*tick_panel)(void*, int panel);
    void (*set_aux_mode)(void*, int slot, int mode);
    void (*set_digit_script)(void*, int slot, int script);
    void (*tick_digit)(void*, int slot);
    void (*publish_camera)(void*, const float position[3]);
};

// Semantic reconstruction of the large player/score UI update at 0x00408D60.
int ScoreRuntimeUi_Update(ScoreRuntimeUiState* state,
                          const ScoreRuntimeUiEnv* env,
                          const ScoreRuntimeUiOps* ops);
