#pragma once

#include <cstdint>

struct MenuFlowState {
    int phase;
    int selection;
    int previous_selection;
    int phase_timer;
    int transition_kind;
    int queued_values[32];
    int queued_count;
    uint16_t saved_config[5];
};

struct MenuFlowInput {
    uint32_t held;
    uint32_t pressed;
};

struct MenuFlowHooks {
    void* context;
    void (*set_phase)(void* context, int phase);
    void (*reset_view)(void* context);
    void (*move_selection)(void* context, MenuFlowState* state, int delta);
    void (*play_change)(void* context);
    void (*refresh_selection)(void* context, int view);
    void (*activate_view)(void* context, int view);
    void (*close_view)(void* context, int view);
    void (*commit_config)(void* context, const uint16_t values[5]);
    void (*launch)(void* context, int transition_kind, int selection);
};

struct ConfigMenuEnv {
    MenuFlowInput input;
    uint16_t config[5];
    const int8_t* availability;
};

// 0x0042F540 - Update the options/configuration menu flow.
int ConfigMenuFlow_Update(MenuFlowState* state, const ConfigMenuEnv* env,
                          const MenuFlowHooks* hooks);

struct StageMenuEnv {
    MenuFlowInput input;
    int stage;
    int shot;
    int fallback_stage;
};

// 0x00430320 - Update the stage/difficulty selection flow.
int StageMenuFlow_Update(MenuFlowState* state, StageMenuEnv* env,
                         const MenuFlowHooks* hooks);

struct ShotMenuEnv {
    MenuFlowInput input;
    int mode;
    int shot;
    uint8_t availability[6];
};

// 0x004306A0 - Update the character/shot selection flow.
int ShotMenuFlow_Update(MenuFlowState* state, ShotMenuEnv* env,
                        const MenuFlowHooks* hooks);
